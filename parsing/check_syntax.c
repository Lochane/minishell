/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:49:44 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/20 19:43:01 by madaguen         ###   ########.fr       */
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
	int	c;
	
	(void) i;
	check = 0;
	c = 0;
	while (args[c])
	{
		if (args[c] == '\'' || args[c] == '"')
		{
			c += get_next_quote(args[c], args + c + 1);
			check = (args[c] == 0);
		}
		if (args[c])
			c++;
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
	if (check_quotes(args, i) != 0)
	{
		data->return_value = 2;
		return (2);
	}
	while (args[i])
	{
		if (check_chevron(args, i) != 0 || check_pipe(args, i) != 0 \
			|| check_ampersand(args, i) != 0\
			|| check_double_quotes(args, i) != 0)
		{
			data->return_value = 2;
			return (2);
		}
		i++;
	}
	return (0);
}
