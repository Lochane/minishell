/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:43:46 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/09 18:19:39 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verif_heredoc(char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	if (s1[i + 1] == '\n' && s2[i + 1] == '\0')
		return (0);
	return (1);
}

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = 0;
}

static unsigned char	*get_file_name(void)
{
	int				i;
	int				fd;
	unsigned char	*file_name;

	i = 5;
	file_name = malloc(sizeof(char) * 16);
	if (!file_name)
		return (NULL);
	ft_strcpy((char *)file_name, "/tmp/");
	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (free(file_name), NULL);
	if (read(fd, file_name + 5, 10) == -1)
		return (free(file_name), close(fd), NULL);
	close(fd);
	while (i < 16)
	{
		file_name[i] = file_name[i] % 26 + 'A';
		i++;
	}
	file_name[15] = 0;
	file_name[5] = '.';
	return (file_name);
}

int	get_fd(unsigned char *file_name, int type)
{
	int	fd;

	if (!type)
		fd = open((const char *)file_name, O_WRONLY | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP);
	else
		fd = open((const char *)file_name, O_RDONLY);
	return (fd);
}

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
		//write(1, "> ", 2);
		line = readline(">");
		if (!line)
		{
			if (g_g != 130)
			{
 				error("minishell: warning: here-document at at line 0\
 delimited by ");
				bash_error("end-of-file (wanted `", (char *)limiter, "')\n");
			}
			break ;
		}
		if (!verif_heredoc(line, (char *)limiter, ft_strlen(limiter)))
			break ;
		ft_putstr_fd(line, tmp_fd);
		free(line);
	}
	free(line);
}

int	get_infile_heredoc(char *limiter)
{
	int				tmp_fd;
	unsigned char	*file_name;
	int				fd;

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
	return (fd);
}
