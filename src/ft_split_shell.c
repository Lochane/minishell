/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:03:04 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/27 14:38:57 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_quote(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\'')
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
		i++;
	}
	else if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
			i++;
		i++;
	}
	return (i);
}

static	size_t	ft_checkword(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && !(s[i] == c))
		{
			count++;
			while (s[i] && s[i] != c)
			{
				if (check_quote(&s[i]))
					i += check_quote(&s[i]);
				else
					i++;
			}
		}
	}
	return (count);
}

static int	len_words(const char *str, char charset)
{
	int	k;

	k = 0;
	while (str[k])
	{
		if (str[k] == charset || !str[k])
			break ;
		if (check_quote(&str[k]))
			k += check_quote(&str[k]);
		else
			k++;
	}
	return (k);
}

static void	fill_words(char **split, const char *str, char charset, int words)
{
	int	j;
	int	k;
	int	i;

	i = 0;
	j = 0;
	k = 0;
	while (i < words)
	{
		while (str[j] && charset == str[j])
			j++;
		k = 0;
		k += len_words(&str[j], charset);
		split[i] = malloc(sizeof(char) * (k + 1));
		if (!split[i])
			ft_free_tab(split, i);
		if (split[i] != 0)
			ft_strlcpy(split[i], &str[j], k);
		j += k;
		i++;
	}
	split[i] = 0;
}

char	**ft_split_shell(char const *s, char c)
{
	size_t	letter_count;
	char	**res;

	if (!s)
		return (NULL);
	letter_count = ft_checkword(s, c);
	res = (char **)malloc(sizeof(char *) * (letter_count + 1));
	if (!res)
		return (NULL);
	fill_words(res, s, c, letter_count);
	return (res);
}
