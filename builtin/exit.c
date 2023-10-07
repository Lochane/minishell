/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/07 23:39:03 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_exit(t_cmd *cmd, t_fd *fd, t_data *data)
{
	int		check;
	int		is_num;
	long	nb;
	int		i;
	int		tty;
	
	(void) cmd;
	(void) fd;
	close(data->fd);
	i = 0;
	tty = isatty(1);
	//print exit seulement si dansun tty?
	check = 0;
	is_num = 0;
	if (!data->cmd || !cmd->arg)
	{
		rl_clear_history();
		printf(RED"exit\n"RESET);
		exit(data->return_value);
	}
	if (cmd->arg[i])
	{
		nb = ft_atol(cmd->arg[0], &check);
		printf("check == %d\n", check);
		printf("nb == %ld\n", nb);
		is_num = check;
		if (i == 0 && !is_num && cmd->arg[i + 1])
		{
			printf(RED"exit\n"RESET);
			write(2, "bash: exit: too many arguments\n", 32);//join fct error
			return (2);
		}
		else if (!is_num)
		{
			//exit avec retour atol
		}
		else
		{
			rl_clear_history();
			data->return_value = nb % 256;
			printf(RED"exit\n"RESET);
			if (cmd->arg[1] == NULL)
				exit(data->return_value);
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