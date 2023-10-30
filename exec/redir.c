/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:43:18 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 22:00:38 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	open_double(t_fd *fd, t_dir *tmp)
{
	if (fd->in > 0)
		close(fd->in);
	if (fd->out > 0)
		close(fd->out);
	fd->out = open((const char *)tmp->file, O_RDONLY | O_CREAT,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	if (fd->out != -1)
	{
		fd->in = fd->out;
		fd->out = 0;
	}
}

void	open_in(t_fd *fd, t_dir *tmp)
{
	if (fd->in > 0)
		close(fd->in);
	if (tmp->token == LESS)
		fd->in = open((const char *)tmp->file, O_RDONLY);
	else
		fd->in = tmp->fd;
}

void	open_out(t_fd *fd, t_dir *tmp)
{
	if (fd->out > 0)
		close(fd->out);
	if (tmp->token == GREAT)
		fd->out = open((const char *)tmp->file, O_TRUNC | O_WRONLY | O_CREAT, \
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	else
		fd->out = open((const char *)tmp->file, O_APPEND | O_WRONLY | O_CREAT, \
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
}

int	open_redir(t_dir *redir, t_fd *fd)
{
	t_dir	*tmp;

	tmp = redir;
	fd->in = -2;
	fd->out = -2;
	while (tmp)
	{
		if (tmp->token == GREAT || tmp->token == GREAT_GREAT)
			open_out(fd, tmp);
		if (tmp->token == LESS || tmp->token == LESS_LESS)
			open_in(fd, tmp);
		if (tmp->token == DOUBLE)
			open_double(fd, tmp);
		if (fd->in == -1 || fd->out == -1)
		{
			ft_error(tmp->file, NULL, 0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
