/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:55:04 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 22:26:56 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_pipe(t_cmd *cmd)
{
	if (cmd->prev_pipe != -1 && dup2(cmd->prev_pipe, 0) == -1)
	{
		perror("dup2 pipe in");
		return (1);
	}
	if (cmd->pipe != -1 && dup2(cmd->pipe, 1) == -1)
	{
		perror("dup2 pipe out");
		return (1);
	}
	return (0);
}

int	dup_redir(t_fd fd, t_data *data)
{
	if (fd.in > 0 && dup2(fd.in, 0) == -1)
	{
		perror("redir dup2 in");
		return (1);
	}
	if (fd.out > 0 && dup2(fd.out, 1) == -1)
	{
		perror("redir dup2 out");
		return (1);
	}
	close_redir(data->cmd);
	return (0);
}

void	close_pipe_child(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe != -1)
		{
			close(cmd->pipe);
			cmd->pipe = -1;
		}
		if (cmd->prev_pipe != -1)
		{
			close(cmd->prev_pipe);
			cmd->pipe = -1;
		}
		cmd = cmd->next;
	}
}

void	close_redir(t_cmd *cmd)
{
	t_dir	*tmp;

	while (cmd)
	{
		tmp = cmd->redirection;
		while (tmp)
		{
			if (tmp->fd != -1)
			{
				close(tmp->fd);
				tmp->fd = -1;
			}
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}
