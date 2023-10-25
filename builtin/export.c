/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/24 18:48:01 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '=' || ft_isdigit(str[0]))
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		if (!check_char(str[i]))
			return (-1);
		i++;
	}
	return (0);
}

int	do_export(t_cmd *cmd, t_fd *fd, t_data *data)
{
	t_lst	*var;
	t_lst	*new;
	int		i;
	int		check;
	char	*message;
	int		is_env;

	(void) cmd;
	(void) fd;
	is_env = 0;
	var = NULL;
	if (cmd->arg)
	{
		i = 0;
		while (cmd->arg[i])
		{
			check = check_var(cmd->arg[i]);
			if (check >= 0)
			{
				ft_get_env(cmd->arg[i], check, data->env, &var);
				if (!var)
				{
					new = ft_new_lst(ft_strdup(cmd->arg[i]));//proteger le malloc
					new->is_env = check;
					ft_add_back(&data->env, new);
				}
				else
				{
					free(var->data);
					var->data = ft_strdup(cmd->arg[i]);
					var->is_env = check;
				}
			}
			else if (check == -1)
			{
				message = ft_join(cmd->arg[i], " is not a valid identifier", 0);//proteger malloc
				ft_error(cmd->cmd, message, 0);
				free(message);
			}
			i++;
		}
	}
	return (0);
}
