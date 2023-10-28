/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/29 00:26:36 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_exit(void)
{
	const char	*exit = "\x1b[91;1mexit\n\x1b[0m\2";

	write(2, exit, ft_strlen(exit));
}

void	exit_no_arg(int tty, t_data *data)
{
	rl_clear_history();
	ft_clear_lst(&data->env);
	close_pipe_child(data->cmd);
	if (tty)
		print_exit();
	manage_data(data, 1);
	if (data->fd != -1)
		close(data->fd);
	exit(data->return_value);
}

void	exit_arg(t_exit var_exit, t_cmd *cmd, t_data *data)
{
	rl_clear_history();
	ft_clear_lst(&data->env);
	if (data->fd != -1)
		close(data->fd);
	close_pipe_child(data->cmd);
	if (!var_exit.check)
	{
		if (var_exit.tty)
			print_exit();
		manage_data(data, 1);
		exit(var_exit.nb % 256);
	}
	else
	{
		if (var_exit.tty)
			print_exit();
		ft_error(cmd->cmd, ": numeric argument required", 0);
		manage_data(data, 1);
		exit(2);
	}
}

int	do_exit(t_cmd *cmd, t_fd *fd, t_data *data)
{
	t_exit	var_exit;

	(void) fd;
	var_exit.i = 0;
	var_exit.tty = isatty(0);
	var_exit.check = 0;
	if (!cmd || !cmd->arg)
		exit_no_arg(var_exit.tty, data);
	if (cmd->arg[var_exit.i])
	{
		var_exit.nb = ft_atol(cmd->arg[0], &var_exit.check);
		if (var_exit.i == 0 && !var_exit.check && cmd->arg[var_exit.i + 1])
		{
			if (var_exit.tty)
				print_exit();
			write(2, "minishell: exit: too many arguments\n", 37);
			return (1);
		}
		exit_arg(var_exit, cmd, data);
	}
	return (0);
}
