/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:49:44 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/09 14:30:07 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			return (ft_syntax_error("syntax error\n"), 1);
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
			return (ft_syntax_error("syntax error\n"), 1);
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
			return (ft_syntax_error("syntax error\n"), 1);
		else
		{
			i++;
			if (!args[i + 1] && (args[i] == '<' || args[i] == '>'))
				return (ft_syntax_error("syntax error\n"), 1);
		}
	}
	return (0);
}

int	check_syntax(char *args, t_data *data)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (check_chevron(args, i) != 0 || check_pipe(args, i) != 0 \
			|| check_ampersand(args, i) != 0 || check_quotes(args, i) != 0 \
			|| check_double_quotes(args, i) != 0)
		{
			data->return_value = 2;
			return (2);
		}
		if (args[i] == '-' && !args[i + 1])
		{
			data->return_value = 127;
			return (ft_syntax_error("command not found\n"), 1);
		}
		i++;
	}
	return (0);
}
