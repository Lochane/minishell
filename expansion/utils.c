/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:16:29 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/11 17:19:05 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

int	check_char(char c)
{
	unsigned int	i;
	const char		*protected = "$:=\"'` ?";

	if (c == 0)
		return (0);
	i = 0;
	while (protected[i])
	{
		if (c == protected[i])
			return (0);
		i++;
	}
	return (1);
}

void	get_buf(t_buf *buffer, unsigned long size)
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

int	get_var_content(t_expand *expand, int *tmp, char *str, t_data data)
{
	t_lst	*lst;

	if (*tmp == 0 && str[1] == '?')
	{
		stack_itoa(expand->nb, data.return_value);
		expand->content = expand->nb;
		return (2);
	}
	else
	{
		expand->content = ft_get_env(&str[1], *tmp, data.env, &lst);
		return (*tmp + 1);
	}
	return (0);
}

void	cpy_var(char *str, int *index, t_buf *buffer, t_data data)
{
	int			tmp;
	int			len;
	t_expand	expand;

	tmp = 0;
	expand.content = NULL;
	while (str[*index + 1 + tmp] && check_char(str[*index + 1 + tmp]))
		tmp++;
	*index += get_var_content(&expand, index, str + *index, data);
	if (expand.content)
	{
		len = ft_strlen(expand.content);
		if (buffer->index + len >= buffer->size)
			get_buf(buffer, len);
		if (!buffer->buf)
			return ;
		while (*expand.content)
		{
			(buffer->buf)[buffer->index++] = *expand.content;
			expand.content++;
		}
	}
	else if ((tmp == 0 && ((str[*index] != '\'') || str[*index] != '"')))
		(buffer->buf)[(buffer->index)++] = '$';
	(buffer->buf)[buffer->index] = 0;
}
