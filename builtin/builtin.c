/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/29 01:05:49 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_built_in(t_cmd *cmd, t_data *data, int check, int index)
{
	const fct	built_in_fct[] = {do_echo, do_cd, do_pwd, do_export, \
	print_env, do_unset, do_exit};
	t_fd		fd;
	int			ret;

	fd.in = 0;
	fd.out = 0;
	if (check && open_redir(cmd->redirection, &fd) == 1)
	{
		if (fd.in > 0)
			close(fd.in);
		if (fd.out > 0)
			close(fd.out);
		return (1);
	}
	ret = built_in_fct[index](cmd, &fd, data);
	if (fd.in > 0)
		close(fd.in);
	if (fd.out > 0)
		close(fd.out);
	return (ret);
}

int	is_built_in(char *s)
{
	int			i;
	const char	*built_in[] = {"echo", "cd", "pwd", "export", \
	"env", "unset", "exit", ((char *)(0))};

	i = 0;
	while (built_in[i])
	{
		if (ft_strcmp(built_in[i], s) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	find_char(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	check_options(char **args, char *options, char *found, char *invalid)
{
	int	i;
	int	l;
	int	check;

	l = 0;
	while (args[l])
	{
		if (args[l][0] == 0 || args[l][0] != '-' || args[l][1] == 0)
			break ;
		i = 1;
		while (args[l][i])
		{
			check = find_char(args[l][i], options);
			if (check == -1)
			{
				if (invalid)
					*invalid = args[l][i];
				return (l);
			}
			found[check] = 1;
			i++;
		}
		l++;
	}
	return (l);
}

void	error_option(char *cmd, char invalid)
{
	int		index;
	char	buffer[100];

	ft_strlcpy(buffer, "minishell: ", 11);
	ft_strlcpy(buffer + 11, cmd, ft_strlen(buffer));
	index = ft_strlen(buffer);
	buffer[index++] = ':';
	buffer[index++] = ' ';
	buffer[index++] = invalid;
	buffer[index] = 0;
	ft_strlcpy(buffer + index, ": invalid option\n", 18);
	write(2, buffer, ft_strlen(buffer));
}
