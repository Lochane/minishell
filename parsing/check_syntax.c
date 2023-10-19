/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:49:44 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/19 20:00:35 by madaguen         ###   ########.fr       */
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

int	get_next_quote(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i + 1);
		i++;
	}
	return (i + 1);
}

int	check_quotes(char *args, int i)
{
	int	check;
	
	check = 0;
	while (args[i])
	{
		if (args[i] == '\'' || args[i] == '"')
		{
			i += get_next_quote(args[i], args + i + 1);
			check = (args[i] == 0);
		}
		else
			i++;
	}
	if (check == 1)
		return (ft_syntax_error("syntax error\n"), 1);
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
		i++;
	}
	return (0);
}
