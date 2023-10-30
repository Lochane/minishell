/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:17:48 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 01:18:44 by madaguen         ###   ########.fr       */
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

void	fail_malloc_expand(t_buffer *buffer)
{
	free (buffer->buf);
	buffer->buf = NULL;
	buffer->size = 0;
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
