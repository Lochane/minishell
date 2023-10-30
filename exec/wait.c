/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 23:47:05 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 23:50:05 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_status(int *status, t_data *data)
{
	int	res;

	res = 0;
	if (WIFEXITED(*status))
	{
		res = WEXITSTATUS(*status);
	}
	else if (WIFSIGNALED(*status))
	{
		res = (WTERMSIG(*status));
		res += 128;
		write(1, "\n", 1);
	}
	data->new_line = 0;
	return (res);
}

int	waiting(t_cmd *cmd, int nb_cmd, t_data *data)
{
	pid_t	pid;
	int		res;
	int		status;
	int		pid_waited;
	t_cmd	*tmp;

	pid_waited = 0;
	tmp = cmd;
	while (pid_waited < nb_cmd)
	{
		if (tmp->pid != -1)
			pid = waitpid(tmp->pid, &status, WNOHANG);
		if (pid > 0 && tmp->pid != -1)
		{
			if (!tmp->next)
				res = get_status(&status, data);
			tmp->pid = -1;
			pid_waited++;
		}
		tmp = tmp->next;
		if (!tmp)
			tmp = cmd;
	}
	return (res);
}
