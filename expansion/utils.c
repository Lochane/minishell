/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:16:29 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/24 18:58:08 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

int	check_char(char c)
{
	if (c == 0)
		return (0);
	if (ft_isalnum(c))
		return (1);
	return (0);
}

int	allowed_char(char c)
{
	const char	*protected = "_?";
	int			i;
	
	i = 0;
	while (protected[i])
	{
		if (protected[i] == c)
			return (0);
		i++;
	}
	return (1);
}

void	get_buf(t_buffer *buffer, unsigned long size)
{
	char			*tmp;
	unsigned long	index;

	if (!buffer->buf)
	{
		buffer->buf = malloc(sizeof(char) * 31);
		if (!buffer->buf)
			return ;
		ft_memset((buffer->buf), '\0', 31);
		buffer->size = 30;
		return ;
	}
	tmp = malloc((buffer->size + size) + 1);
	if (!tmp)
	{
		free (buffer->buf);
		buffer->buf = NULL;
		buffer->size = 0;
		return ;
	}
	index = -1;
	while (++index < buffer->index)
		tmp[index] = buffer->buf[index];
	tmp[index] = 0;
	free(buffer->buf);
	buffer->buf = tmp;
	buffer->size += size;
}

void	stack_itoa(char n[11], unsigned int nb)
{
	unsigned int	size;
	unsigned int	nbr;

	nbr = nb;
	size = 1;
	while (nbr >= 10)
	{
		size++;
		nbr /= 10;
	}
	if (nb == 0)
		n[0] = '0';
	n[size] = 0;
	while (nb > 0)
	{
		n[--size] = (nb % 10) + 48;
		nb /= 10;
	}
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
		if (lst)
			expand->quoted++;
	}
}

int	is_quote(char c, int quote[2])
{
	if (c == '\'' || c == '"')
	{
		if (!quote[0] && !quote[1])
			return (0);
		if (c == '\'')
		{
			if (quote[1])
				return (1);
		}
		if (c == '"')
		{
			if (quote[0])
				return (1);
		}
	}
	return (0);
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
		{
			len = ft_strlen(exp->content);
			if (exp->buffer.index + len >= exp->buffer.size)
				get_buf(&exp->buffer, len);
			if (!exp->buffer.buf)
				return ;
			while (*exp->content)
			{
				(exp->buffer.buf)[exp->buffer.index] = *exp->content;
				printf("buffer == %lu\n", exp->buffer.index);
				exp->content++;
				exp->buffer.index++;
			}
		}
	}
	if ((!exp->content && is_quote(str[exp->index + 1], exp->quote)))
		exp->index++;
	else if (!tmp && ft_isdigit(str[exp->index + 1]))
		exp->index+=2;
	else if ((tmp == 0 && !exp->content) && !ft_isalnum(str[exp->index + 1]))
		(exp->buffer.buf)[(exp->buffer.index)++] = str[exp->index++];
	(exp->buffer.buf)[exp->buffer.index] = 0;
	exp->content = NULL;
}
