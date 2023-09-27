/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:17:38 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/27 17:57:19 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(char *args, int i)
{
	if (args[i] == '|' && !args[i - 1])
		return ((printf(RED"minishell: syntax error near unexpected token '%c'\n"\
		RESET, args[i])), strerror(ERR_SYNTX), ERR_SYNTX);
	if (args[i] == '|' && !args[i + 1])
		return ((printf(RED"minishell: syntax error near unexpected token '%c'\n"\
		RESET, args[i])), strerror(ERR_SYNTX), ERR_SYNTX);
	return (0);
}

int	check_ampersand(char *args, int i)
{
	if (args[i] == '&')
	{
		if (!args[i + 1])
			return ((printf \
			(RED"minishell: syntax error near unexpected token '%c'\n"RESET, \
			args[i])), strerror(ERR_SYNTX), ERR_SYNTX);
		else
		{
			i++;
			if (args[i] == '&' && !args[i + 1])
				return ((printf (RED"minishell: syntax error near unexpected token \
'%c%c'\n"RESET, args[i - 1], args[i])), \
					strerror(ERR_SYNTX), ERR_SYNTX);
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
		return ((printf(RED"minishell: syntax error\n"RESET)), \
					strerror(ERR_SYNTX), ERR_SYNTX);
	return (0);
}
