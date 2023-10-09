/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:16:29 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/09 20:42:22 by lsouquie         ###   ########.fr       */
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
	n[size] = 0;
	if (nb == 0)
		n[0] = '0';
	while (nb > 0)
	{
		n[--size] = (nb % 10) + 48;
		nb /= 10;
	}
}

char	*get_var_content(int *tmp, int *index, char *str, t_data data)
{
	char	nb[11];
	char	*content;
	t_lst	*lst;

	if (*tmp == 0 && str[*index + 1] == '?')
	{
		stack_itoa(nb, data.return_value);
		content = nb;
		(*index) += 2;
	}
	else
	{
		content = ft_get_env(&str[*index + 1], *tmp, data.env, &lst);
		(*index) += *tmp + 1;
	}
	return (content);
}

void	cpy_var(char *str, int *index, t_buf *buffer, t_data data)
{
	int		tmp;
	char	*content;

	tmp = 0;
	while (str[*index + 1 + tmp] && check_char(str[*index + 1 + tmp]))
		tmp++;
	content = get_var_content(&tmp, index, str, data);
	if (content)
	{
		if (buffer->index + ft_strlen(content) >= buffer->size)
			get_buf(buffer, ft_strlen(content));//proteger le null
		while (*content)
		{
			(buffer->buf)[buffer->index++] = *content;
			content++;
		}
	}
	else if ((tmp == 0 && ((str[*index] != '\'') || str[*index] != '"')))
		(buffer->buf)[(buffer->index)++] = '$';
	(buffer->buf)[buffer->index] = 0;
}
