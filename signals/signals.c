/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 19:18:21 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/12 19:23:56 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sig(t_data *data)
{
	dup2(data->fd, 0);
	data->return_value = g_g;
	g_g = 0;
	manage_data(data, 1);
	if (!data->new_line++)
		write(1, "\n", 1);
}

void	ignore_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		close(0);
		g_g = CTRL_C;
	}
	else
		return ;
}

void	restore_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

void	intercept_sig(void)
{
	struct sigaction	ca;

	ca.sa_handler = sig_handler;
	ca.sa_flags = 0;
	sigemptyset(&ca.sa_mask);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sigaction(SIGINT, &ca, NULL);
}