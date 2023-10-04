/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/04 22:45:35 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	do_export(t_cmd *cmd, t_fd fd, t_data *data)
{
	(void) cmd;
	(void) fd;
	t_lst	*var;
	t_lst	*new;
	int		i;

	//a faire en bouvle tant qu'il y a des args
	if (cmd->arg)
	{
		i = 0;
		while (cmd->arg[i])
		{
			if (check_var(cmd->arg[i]))
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
			i++;
		}
	}
	return (0);
}
