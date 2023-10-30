/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:39:32 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 01:22:39 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

void	check_quote(char *str, int q[2], int *index, int *quoted)
{
	while (str[*index] == '\'' || str[*index] == '"')
	{
		if ((str[*index] == '"' && !q[1]) || (str[*index] == '\'' && !q[0]))
		{
			if (str[*index] == '"')
				q[0] = (q[0] != 1);
			else if (str[*index] == '\'')
				q[1] = (q[1] != 1);
			(*index)++;
			(*quoted)++;
		}
		else
			break ;
	}
}

void	fill_buf(char *str, t_data *data, t_expand *exp)
{
	if (!str)
		return ;
	while (str[exp->index])
	{
		if (exp->buffer.index >= exp->buffer.size - 1)
			get_buf(&exp->buffer, 10);
		if (!exp->buffer.buf)
		{
			data->return_value = 12;
			return ;
		}
		check_quote(str, exp->quote, &exp->index, &exp->quoted);
		if (str[exp->index])
		{
			if (str[exp->index] != '$' || exp->quote[1])
				exp->buffer.buf[exp->buffer.index++] = str[exp->index++];
			else
				cpy_var(str, exp, data);
		}
	}
	exp->buffer.buf[exp->buffer.index++] = 0;
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
