/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/03 11:46:29 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_exit(t_cmd *cmd, t_fd fd, t_data *data)
{
	(void) cmd;
	(void) fd;
	int		check;
	//long	nb;
	int	i;

	i = 1;
	check = 0;
	//long	nb;
	if (!cmd->arg)
		exit(data->return_value);
	//nb = ft_atol(cmd->arg[0], &check);
	if (check)//check si different retour si nonnumeric ou overflow ou si les 2 juste non numeric
		return (data->return_value);
	//	exit (nb % 130);
	return (0);
}