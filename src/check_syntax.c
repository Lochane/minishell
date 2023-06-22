/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:49:44 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/20 15:33:12 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_chevron(char *args, int i)
{
	if (args[i] == '>' || args[i] == '<')
	{
		if (!args[i + 1])
			return ((printf("bash: syntax error\n")), 2);
		else
		{
			i++;
			if (!args[i + 1])
				return ((printf("bash: syntax error\n")), 2);
		}
	}
	return (0);
}

int	check_slash(char *args, int i)
{
	if (args[i] == '/')
	{
		if (!args[i + 1])
			return ((printf("bash: %c: Is a directory\n", args[i])), 126);
		else
		{
			i++;
			if (!args[i + 1] || args[i + 1] == '.')
				return ((printf("bash: %c%c: Is a directory\n", args[i - 1], \
					args[i])), 126);
		}	
	}
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

int	check_syntax(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (check_chevron(args, i) != 0 || check_pipe(args, i) != 0 \
			|| check_ampersand(args, i) != 0)
			return (2);
		if (check_slash(args, i) != 0)
			return (126);
		if (args[i] == '-' && !args[i + 1])
			return ((printf("bash: %c: command not found\n", args[i])), 127);
		i++;
	}
	return (0);
}