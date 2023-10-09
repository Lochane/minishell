/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/09 20:31:16 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_env(t_cmd *cmd, t_fd *fd, t_data *data)
{
	int	final_fd;
	char	*str;
	t_lst	*tmp;

	final_fd = 1;
	if (fd->out > 0)
		final_fd = fd->out;
	(void) cmd;
	(void) data;
	tmp = data->env;
	while (tmp)
	{
		str = ft_join(tmp->data, NULL, '\n');
		//proteger echec allocation
		if (write(final_fd, str, ft_strlen(str)) == -1)
		{
			ft_error(cmd->cmd, "write error: ", 1);
			free(str);
			return (125);
		}
		free(str);
		tmp = tmp->next;
	}
	return (0);
}

int	do_pwd(t_cmd *cmd, t_fd *fd, t_data *data)
{
	char	*var;
	int		final_fd;
	char	*str;

	final_fd = 1;
	var = ft_get_env("PWD", 3, data->env, NULL);
	if (fd->out > 0)
		final_fd = fd->out;
	if (!var)
	{
		ft_error(cmd->cmd, "PWD not set", 0);
		return (0);
	}
	str = ft_join(var, NULL, '\n');
	//proteger echec allocation
	if (write(final_fd, str, ft_strlen(str)) == -1)
	{
		printf("errno == %d\n", errno);
		//ft_error(cmd->cmd, ": write error: No space left on device");
		ft_error(cmd->cmd, "write error: ", 1);
		free(str);
		return (1);
	}
	free(str);
	return (0);
}
