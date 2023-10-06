/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/06 19:26:20 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=' && str[i + 1] != '=')
			return (1);
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

	(void) cmd;
	(void) fd;
	if (cmd->arg)
	{
		i = 0;
		while (cmd->arg[i])
		{
			check = check_var(cmd->arg[i]);
			if (check == 1)
			{
				ft_get_env(cmd->arg[i], ft_strlen(cmd->arg[i]), data->env, &var);
				if (!var)
				{
					new = ft_new_lst(cmd->arg[i]);//proteger le malloc
					ft_add_back(&data->env, new);
				}
				else
				{
					free(var->data);
					var->data = ft_strdup(cmd->arg[i]);
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
