/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:00:55 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 01:08:21 by madaguen         ###   ########.fr       */
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
	t_env	env;

	env.final_fd = 1;
	env.inv = 0;
	if (cmd->arg)
	{
		env.check = check_options(cmd->arg, EXPORT_OPTION, env.opt, &env.inv);
		if (env.inv != 0)
		{
			error_option(cmd->cmd, env.inv);
			write(2, ENV_USAGE, ft_strlen(ENV_USAGE));
			return (2);
		}
	}
	if (fd->out > 0)
		env.final_fd = fd->out;
	env.str = get_ptr_env(data->env, get_env_size(data->env));
	if (!env.str)
		return (errno);
	if (write(env.final_fd, env.str, ft_strlen(env.str)) == -1)
		return (ft_error(cmd->cmd, "write error: ", 1), free(env.str), 125);
	free(env.str);
	return (0);
}
