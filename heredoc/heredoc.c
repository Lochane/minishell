/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:43:46 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/30 19:58:26 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(char *str)
{
	ft_putstr_fd(str, 2);
}

void	bash_error(char *s1, char *s2, char *s3)
{
	if (s1)
		error(s1);
	if (s2)
		error(s2);
	if (s3)
		error(s3);
}

void	fill_here_doc(const char *limiter, int tmp_fd)
{
	char	*line;

	(void)limiter;
	while (1)
	{
		line = readline(">");
		if (!line || g_g == 130)
		{
			if (g_g != 130)
			{
				write(2, HERE_DOC_ERROR, ft_strlen(HERE_DOC_ERROR));
				bash_error("end-of-file (wanted `", (char *)limiter, "')\n");
			}
			free(line);
			break ;
		}
		if (!verif_heredoc(line, (char *)limiter, ft_strlen(limiter)))
			break ;
		ft_putstr_fd(line, tmp_fd);
		ft_putstr_fd("\n", tmp_fd);
		free(line);
	}
	free(line);
}

int	get_infile_heredoc(char *limiter)
{
	int		tmp_fd;
	char	*file_name;
	int		fd;

	file_name = get_file_name();
	if (!file_name)
		return (0);
	tmp_fd = get_fd(file_name, 0);
	if (tmp_fd == -1)
		return (0);
	fd = get_fd(file_name, 1);
	unlink((const char *)file_name);
	free(file_name);
	fill_here_doc((const char *)limiter, tmp_fd);
	close(tmp_fd);
	if (g_g == 130)
	{
		close(fd);
		fd = -1;
	}
	return (fd);
}
