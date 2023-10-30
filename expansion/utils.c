/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:16:29 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 01:18:59 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

void	get_buf(t_buffer *buffer, unsigned long size)
{
	char			*tmp;
	unsigned long	index;

	if (!buffer->buf)
	{
		buffer->buf = malloc(sizeof(char) * 31);
		if (buffer->buf)
		{
			ft_memset((buffer->buf), '\0', 31);
			buffer->size = 30;
		}
		return ;
	}
	tmp = malloc((buffer->size + size) + 1);
	if (!tmp)
		return (fail_malloc_expand(buffer));
	index = -1;
	while (++index < buffer->index)
		tmp[index] = buffer->buf[index];
	tmp[index] = 0;
	free(buffer->buf);
	buffer->buf = tmp;
	buffer->size += size;
}

void	get_var_content(t_expand *expand, int *tmp, char *str, t_data *data)
{
	t_lst	*lst;

	if (str[1] == '?')
	{
		stack_itoa(expand->nb, data->return_value);
		expand->content = expand->nb;
		expand->index += 2;
	}
	else
	{
		expand->content = ft_get_env(&str[1], *tmp - 1, data->env, &lst);
		expand->index += *tmp;
	}
}

void	fill_var(int *len, t_expand *exp, t_data *data)
{
	*len = ft_strlen(exp->content);
	if (exp->buffer.index + *len >= exp->buffer.size)
	{
		get_buf(&exp->buffer, *len);
		if (!exp->buffer.buf)
		{
			data->return_value = 12;
			return ;
		}
	}
	if (!exp->buffer.buf)
		return ;
	while (*exp->content)
	{
		(exp->buffer.buf)[exp->buffer.index] = *exp->content;
		exp->content++;
		exp->buffer.index++;
	}
}

void	cpy_var(char *str, t_expand *exp, t_data *data)
{
	int	tmp;
	int	len;

	tmp = 0;
	if (ft_isalpha(str[exp->index + 1]) || !allowed_char(str[exp->index + 1]))
	{
		tmp++;
		while (check_char(str[exp->index + tmp]))
			tmp++;
		get_var_content(exp, &tmp, str + exp->index, data);
		if (exp->content)
			fill_var(&len, exp, data);
	}
	if ((!exp->content && is_quote(str[exp->index + 1], exp->quote)))
		exp->index++;
	else if (!tmp && ft_isdigit(str[exp->index + 1]))
		exp->index += 2;
	else if ((tmp == 0 && !exp->content) && !ft_isalnum(str[exp->index + 1]))
		(exp->buffer.buf)[(exp->buffer.index)++] = str[exp->index++];
	(exp->buffer.buf)[exp->buffer.index] = 0;
	exp->content = NULL;
}
