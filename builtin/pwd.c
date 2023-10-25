/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/25 20:08:48 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env_size(t_lst *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i += ft_strlen(lst->data);
		lst = lst->next;
		i++;
	}
	return (i);
}

char	*get_ptr_env(t_lst *lst, int size)
{
	char	*line;
	int		i;
	int		j;

	line = malloc(size + 1);
	if (!line)
		return (fail_malloc(), NULL);
	j = 0;
	while (lst)
	{
		i = 0;
		if (lst->is_env)
		{
			while (lst->data[i])
				line[j++] = lst->data[i++];
			line[j++] = '\n';
		}
		lst = lst->next;
	}
	line[j] = 0;
	return (line);
}

int	print_env(t_cmd *cmd, t_fd *fd, t_data *data)
{
	int	final_fd;
	char	*str;

	final_fd = 1;
	if (fd->out > 0)
		final_fd = fd->out;
	(void) cmd;
	(void) data;
	str = get_ptr_env(data->env, get_env_size(data->env));
	if (!str)
		return (errno);
	if (write(final_fd, str, ft_strlen(str)) == -1)
		{
			ft_error(cmd->cmd, "write error: ", 1);
			free(str);
			return (125);
		} 
	free(str);
	return (0);
}

int	do_pwd(t_cmd *cmd, t_fd *fd, t_data *data)
{
	char	*var;
	int		final_fd;
	char	*str;
	char	invalid;
	int		check;
	char	option[0];

	final_fd = 1;
	invalid = 0;
	if (cmd->arg)
	{
		check = check_options(cmd->arg ,PWD_OPTION, option, &invalid);
		if (invalid != 0)
		{
			error_option(cmd->cmd, invalid);
			return (2);
		}
	}
	var = ft_get_env("PWD", 3, data->env, NULL);
	if (fd->out > 0)
		final_fd = fd->out;
	if (!var)
	{
		ft_error(cmd->cmd, "PWD not set", 0);
		return (0);
	}
	str = ft_join(var, NULL, '\n');
	if (write(final_fd, str, ft_strlen(str)) == -1)
	{
		ft_error(cmd->cmd, "write error: ", 1);
		free(str);
		return (1);
	}
	free(str);
	return (0);
}
