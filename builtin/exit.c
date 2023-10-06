/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/06 21:52:56 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_exit(t_cmd *cmd, t_fd *fd, t_data *data)
{
	int		check;
	long	nb;
	int	i;
	
	(void) cmd;
	(void) fd;
	i = 1;
	check = 0;
	//long	nb;
	if (!data->cmd || !cmd->arg)
	{
		printf(RED"exit\n"RESET);
		exit(data->return_value);
	}
	nb = ft_atol(cmd->arg[0], &check);
	printf("check == %d\n", check);
	printf("nb == %ld\n", nb);
	if (check)//check si different retour si nonnumeric ou overflow ou si les 2 juste non numeric
		return (data->return_value);
	//	exit (nb % 130);
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