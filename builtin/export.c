/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/29 00:55:38 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	succes_export(t_export *export, t_cmd *cmd, t_data *data)
{
	ft_get_env(cmd->arg[export->i], export->check, data->env, &export->var);
	export->content = ft_strdup(cmd->arg[export->i]);
	if (!export->content)
		return (fail_malloc(), 12);
	if (!export->var)
	{
		export->var = ft_new_lst(export->content);
		if (!export->var)
			return (free(export->content), fail_malloc(), 12);
		ft_add_back(&data->env, export->var);
	}
	else
	{
		free(export->var->data);
		export->var->data = export->content;
		if (!export->var->data)
			return (fail_malloc(), 12);
	}
	export->var->is_env = export->check;
	return (0);
}

int	in_loop(t_export *export, t_cmd *cmd, t_data *data)
{
	export->check = check_var(cmd->arg[export->i]);
	if (export->check >= 0)
	{
		if (succes_export(export, cmd, data))
			return (12);
	}
	else if (export->check == -1)
	{
		if (!cmd->arg[export->i][0])
		export->message = ft_join("''", ": is not a valid identifier", 0);
		else
			export->message = ft_join(cmd->arg[export->i], \
			": is not a valid identifier", 0);
		if (!export->message)
			return (fail_malloc(), 12);
		ft_error(cmd->cmd, export->message, 0);
		free(export->message);
	}
	return (0);
}

int	do_export(t_cmd *cmd, t_fd *fd, t_data *data)
{
	t_export	export;
	int			check;

	(void) fd;
	init_export(&export);
	if (cmd->arg)
	{
		if (verif_option(&export, cmd))
			return (2);
		while (cmd->arg[export.i])
		{
			check = in_loop(&export, cmd, data);
			if (check)
				return (check);
			export.i++;
		}
	}
	return (0);
}
