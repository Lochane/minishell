/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:17:38 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/11 18:33:19 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(char *args, int i)
{
	if (args[i] == '|' && !args[i - 1])
		return ((printf("\x1b[91;1mbash: syntax error near unexpected token '%c'\n\x1b[0m", \
			args[i])), strerror(ERR_SYNTX), ERR_SYNTX);
	if (args[i] == '|' && !args[i + 1])
		return ((printf("\x1b[91;1mbash: syntax error near unexpected token '%c'\n\x1b[0m", \
			args[i])), strerror(ERR_SYNTX), ERR_SYNTX);
	return (0);
}

int	check_ampersand(char *args, int i)
{
	if (args[i] == '&')
	{
		if (!args[i + 1])
			return ((printf \
			("\x1b[91;1mbash: syntax error near unexpected token '%c'\n\x1b[0m", args[i])), \
				strerror(ERR_SYNTX), ERR_SYNTX);
		else
		{
			i++;
			if (args[i] == '&' && !args[i + 1])
				return ((printf ("\x1b[91;1mbash: syntax error near unexpected token\
				 '%c%c'\n\x1b[0m", args[i - 1], args[i])), \
					strerror(ERR_SYNTX), ERR_SYNTX);
		}
	}
	return (0);
}