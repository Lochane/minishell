/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:58:46 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 20:29:21 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	verif_heredoc(char *s1, const char *s2, int n)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i] && i < n)
		i++;
	if (!s1[i] && !s2[i])
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

char	*get_file_name(void)
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
	return ((char *)file_name);
}

int	get_fd(char *file_name, int type)
{
	int				fd;
	unsigned char	*file;

	file = (unsigned char *)file_name;
	if (!type)
		fd = open((const char *)file, O_WRONLY | O_CREAT, \
			S_IRUSR | S_IWUSR | S_IRGRP);
	else
		fd = open((const char *)file_name, O_RDONLY);
	return (fd);
}
