/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:18:47 by lsouquie          #+#    #+#             */
/*   Updated: 2023/05/04 13:59:25 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*clean_it_gnl(char *stash)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	if (ft_strlen_gnl(stash) == 0)
		return (free(stash), NULL);
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	temp = malloc (sizeof(char *) * (ft_strlen_gnl(stash) - i) + 1);
	if (!temp)
		return (free(stash), NULL);
	while (stash[i])
		temp[j++] = stash[i++];
	temp[j] = '\0';
	return (free(stash), temp);
}

char	*add_it_gnl(char *stash)
{
	int		i;
	int		len;
	char	*line;

	len = 0;
	i = 0;
	if (stash == NULL || stash[i] == 0)
		return (NULL);
	while (stash[len] != '\0' && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	line = malloc(sizeof(char *) * (len + 1));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*stash_it_gnl(char *stash, int fd)
{
	char		*buf;
	ssize_t		readed;

	readed = 1;
	if (stash && ft_strchr_gnl(stash, '\n'))
		return (stash);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	*buf = '\0';
	while (readed != 0 && !ft_strchr_gnl(buf, '\n'))
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
			return (free(buf), NULL);
		buf[readed] = '\0';
		stash = ft_strjoin_gnl(stash, buf);
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = 0;
	stash = stash_it_gnl(stash, fd);
	line = add_it_gnl(stash);
	if (ft_strlen_gnl(line) == 0)
		line = NULL;
	stash = clean_it_gnl(stash);
	return (line);
}
