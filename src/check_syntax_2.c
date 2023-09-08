/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 16:17:38 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/08 16:59:55 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe(char *args, int i)
{
	if (args[i] == '|' && !args[i - 1])
		return ((printf("bash: syntax error near unexpected token '%c'\n", \
			args[i])), 2);
	if (args[i] == '|' && !args[i + 1])
		return ((printf("bash: syntax error near unexpected token '%c'\n", \
			args[i])), 2);
	return (0);
}

int	check_ampersand(char *args, int i)
{
	if (args[i] == '&')
	{
		if (!args[i + 1])
			return ((printf \
			("bash: syntax error near unexpected token '%c'\n", args[i])), 2);
		else
		{
			i++;
			if (args[i] == '&' && !args[i + 1])
				return ((printf ("bash: syntax error near unexpected token\
				 '%c%c'\n", args[i - 1], args[i])), 2);
		}
	}
	return (0);
}