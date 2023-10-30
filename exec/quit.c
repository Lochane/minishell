/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:37:12 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 00:21:19 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_and_exit(int res, t_fork fork, t_data *data)
{
	close_redir(data->cmd);
	close_pipe_child(data->cmd);
	free_child(fork, data);
	exit(res);
}

void	free_child(t_fork fork, t_data *data)
{
	if (data->fd > -1)
		close(data->fd);
	data->fd = -1;
	ft_free_tab(fork.path, tab_size(fork.path));
	fork.path = NULL;
	free(fork.cmd);
	fork.cmd = NULL;
	free(fork.pathed);
	rl_clear_history();
	manage_data(data, 1);
	ft_clear_lst(&data->env);
	free(fork.env);
}

void	quit_fail_redir(t_fork fork, t_data *data)
{
	if (fork.fd.in > 0)
		close(fork.fd.in);
	if (fork.fd.out > 0)
		close(fork.fd.out);
	free_and_exit(1, fork, data);
}
