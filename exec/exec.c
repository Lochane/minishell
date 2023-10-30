/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:36:24 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 00:27:44 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**join_cmd(char *cmd, char **arg)
{
	char	**new;
	int		size;
	int		i;

	i = 1;
	if (arg)
		size = tab_size(arg) + 1;
	else
		size = 1;
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = arg[i - 1];
		i++;
	}
	new[i] = NULL;
	new[0] = cmd;
	return (new);
}

void	do_redir(t_cmd *cmd_lst, t_fork *fork, t_data *data)
{
	if (dup_pipe(cmd_lst) == 1)
		free_and_exit(1, *fork, data);
	if (open_redir(cmd_lst->redirection, &fork->fd) == 1)
		quit_fail_redir(*fork, data);
	if (dup_redir(fork->fd, data) == 1)
		free_and_exit(1, *fork, data);
	if (fork->fd.in > 0)
	{
		close(fork->fd.in);
		fork->fd.in = -1;
	}
	if (fork->fd.out > 0)
	{
		close(fork->fd.out);
		fork->fd.out = -1;
	}
}

void	exec(t_cmd *cmd_lst, t_data *data)
{
	t_fork	fork;
	int		built_in;

	init_exec(data, &fork, &built_in, cmd_lst->cmd);
	do_redir(cmd_lst, &fork, data);
	if (built_in != -1 && (do_built_in(cmd_lst, data, 0, built_in), 1))
		free_and_exit(data->return_value, fork, data);
	fork.env = lst_to_tab(data->env);
	if (!fork.env)
		free_and_exit(errno, fork, data);
	fork.path = ft_split(get_path(fork.env), ':');
	fork.cmd = join_cmd(cmd_lst->cmd, cmd_lst->arg);
	if (!fork.cmd)
		return (fail_malloc(), free_and_exit(errno, fork, data));
	fork.pathed = check_access(fork.cmd[0], fork.path);
	if (!fork.pathed)
		free_and_exit(127 - (g_g == 126), fork, data);
	close_pipe_child(data->cmd);
	execve(fork.pathed, fork.cmd, fork.env);
	free_and_exit(0, fork, data);
}

void	close_pipe_parent(t_var *var)
{
	if (var->tmp->pipe != -1)
		close(var->tmp->pipe);
	if (var->tmp->prev_pipe != -1)
		close(var->tmp->prev_pipe);
	var->tmp = var->tmp->next;
}

int	handle_cmds(t_cmd *cmd, t_data *data)
{
	t_var	var;

	init_handle_cmds(&var, cmd);
	if (!cmd->next && var.is_builtin != -1)
		return (do_built_in(cmd, data, 1, var.is_builtin));
	ignore_sig();
	while (var.tmp)
	{
		if (init_pipe(&var))
			return (errno);
		var.tmp->pid = fork();
		if (var.tmp->pid == -1)
		{
			write(2, "error to create process\n", 24);
			perror("fork : ");
			return (127);
		}
		else if (var.tmp->pid == 0)
			exec(var.tmp, data);
		var.i++;
		close_pipe_parent(&var);
	}
	return (waiting(cmd, var.i, data));
}
