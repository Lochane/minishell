/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:36:52 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 00:27:11 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_fork(t_fork *fork)
{
	fork->env = NULL;
	fork->path = NULL;
	fork->pathed = NULL;
	fork->cmd = NULL;
}

void	init_handle_cmds(t_var *var, t_cmd *cmd)
{
	var->tmp = cmd;
	var->i = 0;
	var->pip[0] = -1;
	var->pip[1] = -1;
	var->is_builtin = is_built_in(cmd->cmd);
}

int	init_pipe(t_var *var)
{
	if (var->tmp->next)
	{
		if (pipe(var->pip) == -1)
			return (ft_error("pipe error:", NULL, 0), errno);
		var->tmp->pipe = var->pip[1];
		var->tmp->next->prev_pipe = var->pip[0];
	}
	return (0);
}

void	init_exec(t_data *data, t_fork *fork, int *built_in, char *cmd)
{
	restore_sig();
	if (data->fd > -1)
		close(data->fd);
	data->fd = -1;
	init_fork(fork);
	*built_in = is_built_in(cmd);
}
