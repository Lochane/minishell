/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/13 20:09:09 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_exit(t_cmd *cmd, t_fd *fd, t_data *data)
{
	int		check;
	long	nb;
	int		i;
	int		tty;
	
	(void) cmd;
	(void) fd;
	i = 0;
	tty = isatty(0);
	check = 0;
	if (!data->cmd || !cmd->arg)
	{
		rl_clear_history();
		ft_clear_lst(&data->env);
		close_pipe_child(data->cmd);
		if (tty)
			printf(RED"exit\n"RESET);
		manage_data(data, 1);
		if (data->fd != -1)
			close(data->fd);
		exit(data->return_value);
	}
	if (cmd->arg[i])
	{
		nb = ft_atol(cmd->arg[0], &check);
		if (i == 0 && !check && cmd->arg[i + 1])
		{
			if (tty)
				printf(RED"exit\n"RESET);
			write(2, "minishell: exit: too many arguments\n", 32);//join fct error
			return (1);
		}
		rl_clear_history();
		ft_clear_lst(&data->env);
		if (data->fd != -1)
			close(data->fd);
		close_pipe_child(data->cmd);
		if (!check)
		{
			if (tty)
				printf(RED"exit\n"RESET);	
			manage_data(data, 1);
			exit(nb % 256);
		}
		else
		{
			if (tty)
				printf(RED"exit\n"RESET);
			ft_error(cmd->cmd, ": numeric argument required", 0);
			manage_data(data, 1);
			exit(2);
		}
	}	
	return (0);
}
//utliser join pool fct error qui set un double tab et qui print a la fin
/*
madaguen@made-f0Cr6s5:~$ exit 12dasbs 12asfL
exit
bash: exit: 12dasbs: numeric argument required
madaguen@made-f0Cr6s5:~$ $SHLVL
2: command not found
madaguen@made-f0Cr6s5:~$ bash
madaguen@made-f0Cr6s5:~$ 
madaguen@made-f0Cr6s5:~$ exit 12 12
exit
bash: exit: too many arguments
madaguen@made-f0Cr6s5:~$  $SHLVL
3: command not found

si un arg il auitte si non numerique erreur et quitte
si exit a plusieurs arg dont le 1er est numeriques, il met un messqge d'erreur et ne quitte pas
si un ou plusieurs arg non numeriques il mets un messge d'erreur et il quitte 
et si on overflow le long max il met un message d'erreur arg non numerique et quitte*/