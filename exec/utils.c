/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:55:03 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/06 21:46:17 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long ft_atol(char *nbr, int *check)
{
	int				sign;
	unsigned long	nb;
	unsigned long	max;

	nb = 0;
	max = (unsigned long) LONG_MAX + 3;
	sign = 0;
	while ((nbr && *nbr == 32) || (*nbr <= 13 && *nbr >= 9))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			sign = 1;
		nbr++;
	}
	while (*nbr && *nbr <= '9' && *nbr >= '0' && nb < max)
		nb = nb * 10 + *nbr++ - '0';
	if ((nb > max - 3 && !sign) || (nb > max - 2 && sign) || (*nbr >= '0' && *nbr <= '9'))
		*check = 1;
	else if (*nbr != 0)
		*check = 2;
	//1 si overflow 2 si non numeric? 0 si ok
	if (sign)
		nb *= -1;
	return (nb);
}

int	ft_strcmp(const char *s, const char *s1)
{
	int	i;
	
	i = 0;
	if (!s || !s1)
		return (s - s1);
	while (s[i] && s[i] == s1[i])
		i++;
	return (s[i] - s1[i]);
}

char	*ft_join(char *s1, char *s2, char c)
{
	int		i;
	int		size;
	char	*s3;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	if (c)
		size = size + 1;
	s3 = malloc(sizeof(char) * size + 1);
	if (!s3)
		return (NULL);
	while (s1 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	if (c)
		s3[i++] = c;
	while (s2 && s2[j])
		s3[i++] = s2[j++];
	s3[i] = 0;
	return (s3);
}

void	ft_error(char *message, char *message2, int info)
{
	char	*str;
	char	*str2;
	char	*err;

	str2 = NULL;
	str = ft_join("minishell: ", message, 0);//protgeger alloc
	if (!message2 && !info)
		str2 = ft_join(str, strerror(errno), ' ');//proteger les allocs
	else if (message && info)
	{
		err = ft_join(message2, strerror(errno), ' ');//proteger allocs
		str2 = ft_join(str, err, 0);//proteger les allocs
		free(err);
	}
	else if (message)
		str2 = ft_join(str, message2, ' ');//proteger les allocs
	free(str);
	str = ft_join(str2, NULL, '\n');
	free(str2);
	write(2, str, ft_strlen(str));
	free(str);
}
