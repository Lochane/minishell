/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:49:44 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/11 18:36:30 by lsouquie         ###   ########.fr       */
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
			return ((printf("\x1b[91;1mbash: syntax error\n\x1b[0m")), \
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
			return ((printf("\x1b[91;1mbash: syntax error\n\x1b[0m")), \
				strerror(ERR_SYNTX), ERR_SYNTX);
	}
	return (0);
}

int	check_chevron(char *args, int i)
{
	if (args[i] == '>' || args[i] == '<')
	{
		if (!args[i + 1])
			return ((printf("\x1b[91;1mbash: syntax error\n\x1b[0m")), \
				strerror(ERR_SYNTX), ERR_SYNTX);
		else
		{
			i++;
			if (!args[i + 1])
				return ((printf("\x1b[91;1mbash: syntax error\n\x1b[0m")), \
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
			return ((printf("\x1b[91;1mbash: %c: Is a directory\n\x1b[0m", args[i])), \
				strerror(ERR_DIR), ERR_DIR);
		else
		{
			i++;
			if (!args[i + 1] || args[i + 1] == '.')
				return ((printf("\x1b[91;1mbash: %c%c: Is a directory\n\x1b[0m", args[i - 1], \
					args[i])), strerror(ERR_DIR), ERR_DIR);
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
			return ((printf("\x1b[91;1mbash: %c: command not found\n\x1b[0m", args[i]), \
				strerror(ERR_CMD)), ERR_CMD);
		i++;
	}
	return (0);
}