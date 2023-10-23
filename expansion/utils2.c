/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:39:32 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/23 23:46:57 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

void	check_quote(char *str, int quote[2], int *index, int *quoted)
{
	if ((str[*index] == '"' && !quote[1]) || (str[*index] == '\'' && !quote[0]))
	{
		if (str[*index] == '"')
			quote[0] = (quote[0] != 1);
		else if (str[*index] == '\'')
			quote[1] = (quote[1] != 1);
		(*index)++;
		(*quoted)++;
		if (str[*index] == str[*index - 1])
		{
			quote[0] = 0;
			quote[1] = 0;
			(*index)++;
		}
	}
}

void	fill_buf(char *str, t_data *data, t_expand *expand)
{
	if (!str)
		return ;
	while (str[expand->index])
	{
		if (expand->buffer.index >= expand->buffer.size - 1)
			get_buf(&expand->buffer, 10);
		if (!expand->buffer.buf)
			return ;
		check_quote(str, expand->quote, &expand->index, &expand->quoted);
		if (str[expand->index])
		{
			if (str[expand->index] != '$' || expand->quote[1])
				expand->buffer.buf[expand->buffer.index++] = str[expand->index++];
			else
				cpy_var(str, expand, data);
		}
	}
	expand->buffer.buf[expand->buffer.index++] = 0;
}

void	init_expand(t_expand *expand)
{
	expand->buffer.index = 0;
	expand->buffer.buf = NULL;
	expand->buffer.size = 0;
	expand->content = NULL;
	expand->index = 0;
	expand->quote[0] = 0;
	expand->quote[1] = 0;
	expand->quoted = 0;
}

char	*do_expand(char **str, t_data *data)
{
	t_expand	expand;

	init_expand(&expand);
	if (!*str)
		return (NULL);
	get_buf(&expand.buffer, 0);
	if (!expand.buffer.buf)
	{
		free(*str);
		*str = expand.buffer.buf;
		*str = NULL;
		return (NULL);
	}
	fill_buf(*str, data, &expand);
	expand.buffer.buf[expand.buffer.index] = 0;
	if (!*expand.buffer.buf && !expand.quoted)
	{
		free(expand.buffer.buf);
		free(*str);
		*str = NULL;
		expand.buffer.buf = NULL;
	}
	return (expand.buffer.buf);
}
