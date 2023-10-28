/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/28 22:22:31 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_var(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '=' || !ft_isalpha(str[0]))
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
	char	*content;
	char	option[0];
	char	invalid;

	(void) cmd;
	(void) fd;
	is_env = 0;
	var = NULL;
	invalid = 0;
	if (cmd->arg)
	{
		check = check_options(cmd->arg ,EXPORT_OPTION, option, &invalid);
		if (invalid != 0)
		{
			error_option(cmd->cmd, invalid);
			write(2, EXPORT_USAGE, ft_strlen(EXPORT_USAGE));
			return (2);
		}
		i = 0;
		while (cmd->arg[i])
		{
			check = check_var(cmd->arg[i]);
			if (check >= 0)
			{
				ft_get_env(cmd->arg[i], check, data->env, &var);
				if (!var)
				{
					content = ft_strdup(cmd->arg[i]);
					if (!content)
						return (fail_malloc(), 12);
					new = ft_new_lst(content);
					if (!new)
						return (free(content), fail_malloc(), 12);
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
				if (!cmd->arg[i][0])
					message = ft_join("''", ": is not a valid identifier", 0);
				else
					message = ft_join(cmd->arg[i], ": is not a valid identifier", 0);
				if (!message)
					return (fail_malloc(), 12);
				ft_error(cmd->cmd, message, 0);
				free(message);
			}
			i++;
		}
	}
	return (0);
}
