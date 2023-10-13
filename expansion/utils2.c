/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:39:32 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/13 17:02:54 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

int	check_quote(char *str, int quote[2], int *index)
{
	if ((str[*index] == '"' && !quote[1]) || (str[*index] == '\'' && !quote[0]))
	{
		if (str[*index] == '"')
			quote[0] = (quote[0] != 1);
		else if (str[*index] == '\'')
			quote[1] = (quote[1] != 1);
		(*index)++;
		return (1);
	}
	return (0);
}

void	fill_buf(char *str, t_data data, int quote[2], t_buf *buf)
{
	int	index;

	index = quote[2];
	if (!str)
		return ;
	while (str[index])
	{
		if (buf->index >= buf->size - 1)
			get_buf(buf, 10);
		if (buf->index >= buf->size - 1)
			get_buf(buf, 0);
		if (!buf->buf)
			return ;
		if (!check_quote(str, quote, &index))
		{
			if (str[index] != '$' || quote[1])
				buf->buf[buf->index++] = str[index++];
			else
				cpy_var(str, &index, buf, data);
		}
		buf->buf[buf->index] = 0;
	}
	quote[2] = index;
}

char	*do_expand(char **str, t_data data)
{
	int		index;
	int		quote[3];
	t_buf	buffer;

	buffer.index = 0;
	quote[0] = 0;
	quote[1] = 0;
	quote[2] = 0;
	buffer.buf = NULL;
	buffer.size = 0;
	if (!str)
		return (NULL);
	get_buf(&buffer, 0);
	if (!buffer.buf)
	{
		free(*str);
		*str = buffer.buf;
		return (NULL);
	}
	fill_buf(*str, data, quote, &buffer);
	index = quote[2];
	buffer.buf[buffer.index] = 0;
	if (!buffer.index)
	{
		free(buffer.buf);
		free(*str);
		buffer.buf = NULL;
		*str = buffer.buf;
		return (NULL);
	}
	return (buffer.buf);
}
