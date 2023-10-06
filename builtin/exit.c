/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/06 20:55:26 by madaguen         ###   ########.fr       */
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
	printf("nb == %ld\n", nb);
	if (check)//check si different retour si nonnumeric ou overflow ou si les 2 juste non numeric
		return (data->return_value);
	//	exit (nb % 130);
	return (0);
}