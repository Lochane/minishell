/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:49:44 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/27 17:47:27 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_double_quotes(char *args, int i)
{
	static int	check;

	if (args[i] == '\"' && check == 0)
	{
		i++;
		while (args[i])
		{
			if (args[i] == '\"')
				check = 1;
			i++;
		}
		if (check == 0)
			return ((printf(RED"minishell: syntax error\n"RESET)), \
				strerror(ERR_SYNTX), ERR_SYNTX);
	}
	return (0);
}

int	check_quotes(char *args, int i)
{
	static int	check;

	if (args[i] == '\'' && check == 0)
	{
		i++;
		while (args[i])
		{
			if (args[i] == '\'')
				check = 1;
			i++;
		}
		if (check == 0)
			return ((printf(RED"minishell: syntax error\n"RESET)), \
				strerror(ERR_SYNTX), ERR_SYNTX);
	}
	return (0);
}

int	check_chevron(char *args, int i)
{
	if (args[i] == '>' || args[i] == '<')
	{
		if (count_chevron(args, i) != 0)
			return (1);
		if (!args[i + 1])
			return ((printf(RED"minishell: syntax error\n"RESET)), \
				strerror(ERR_SYNTX), ERR_SYNTX);
		else
		{
			i++;
			if (!args[i + 1] && (args[i] == '<' || args[i] == '>'))
				return ((printf(RED"minishell: syntax error\n"RESET)), \
					strerror(ERR_SYNTX), ERR_SYNTX);
		}
	}
	return (0);
}

int	check_slash(char *args, int i)
{
	if (args[i] == '/')
	{
		if (!args[i + 1])
			return ((printf(RED"minishell: %c: Is a directory\n"RESET, \
			args[i])), strerror(ERR_DIR), ERR_DIR);
		else
		{
			i++;
			if (!args[i + 1] || args[i + 1] == '.')
				return ((printf(RED"minishell: %c%c: Is a directory\n"RESET, \
				args[i - 1], args[i])), strerror(ERR_DIR), ERR_DIR);
		}	
	}
	return (0);
}

int	check_syntax(char *args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (check_chevron(args, i) != 0 || check_pipe(args, i) != 0 \
			|| check_ampersand(args, i) != 0 || check_quotes(args, i) != 0 \
			|| check_double_quotes(args, i) != 0)
			return (2);
		if (check_slash(args, i) != 0)
			return (ERR_DIR);
		if (args[i] == '-' && !args[i + 1])
			return ((printf(RED"minishell: %c: command not found\n"RESET, \
			args[i]), strerror(ERR_CMD)), ERR_CMD);
		i++;
	}
	return (0);
}
