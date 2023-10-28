/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:50:43 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 00:51:17 by madaguen         ###   ########.fr       */
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

int	verif_option(t_export *export, t_cmd *cmd)
{
	export->check = check_options(cmd->arg, EXPORT_OPTION, \
	export->option, &export->invalid);
	if (export->invalid != 0)
	{
		error_option(cmd->cmd, export->invalid);
		write(2, EXPORT_USAGE, ft_strlen(EXPORT_USAGE));
		return (2);
	}
	return (0);
}

void	init_export(t_export *export)
{
	export->is_env = 0;
	export->var = NULL;
	export->invalid = 0;
	export->i = 0;
}
