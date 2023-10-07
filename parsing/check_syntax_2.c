/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:17:38 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/07 15:20:05 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_syntax_error(char *message)
{
	char	*str;

	str = ft_strjoin("minishell: ", message);
	write(1, RED, 7);
	write(2, str, ft_strlen(str));
	write(1, RESET, 4);
	free(str);
}

int	check_pipe(char *args, int i)
{
	if (args[i] == '|' && !args[i - 1])
		return (ft_syntax_error("syntax error near unexpected token\n"), 1);
	if (args[i] == '|' && !args[i + 1])
		return (ft_syntax_error("syntax error near unexpected token\n"), 1);
	return (0);
}

int	check_ampersand(char *args, int i)
{
	if (args[i] == '&')
	{
		if (!args[i + 1])
			return (ft_syntax_error("syntax error near unexpected token\n"), 1);
		else
		{
			i++;
			if (args[i] == '&' && !args[i + 1])
			return (ft_syntax_error("syntax error near unexpected token\n"), 1);
		}
	}
	return (0);
}


int	count_chevron(char *args, int i)
{
	int	count;

	count = 0;
	while (args[i] && (args[i] == '>' || args[i] == '<'))
	{
		if (args[i] == '<' || args[i] == '>')
		{
			while (args[i] && (args[i] == '<' || args[i] == '>'))
			{
				i++;
				count++;
			}
		}
		i++;
	}
	if (count > 2)
		return (ft_syntax_error("syntax error\n"), 1);
	return (0);
}
