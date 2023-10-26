/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/26 18:37:23 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_var_cmp(char *s1, int size, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s1[i] != '=') && s1[i] == s2[i] && i < size)
		i++;
	if ((!s1[i] || !ft_isalnum(s1[i])) && (!s2[i] || s2[i] == '='))
		return (0);
	else
		return (1);
}

char	*ft_get_env(char *var, int size, t_lst *env, t_lst **lst)
{
	t_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_var_cmp(var, size, tmp->data) && tmp->is_env)
		{
			if (lst)
				*lst = tmp;
			return (&tmp->data[tmp->size + 1]);
		}
		tmp = tmp->next;
	}
	if (lst)
		*lst = NULL;
	return (NULL);
}

int	do_built_in(t_cmd *cmd, t_data *data, int check)
{
	const char		*built_in_name[] = BUILT_IN_LIST;
	const fct	built_in_fct[]  = {do_echo, do_cd, do_pwd, do_export, print_env, do_unset, do_exit};
	int		i;
	t_fd	fd;
	int		ret;

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
	i = 0;
	while (built_in_name[i])
	{
		if (ft_strcmp(built_in_name[i], cmd->cmd) == 0)
			break ;
		i++;
	}
	ret = built_in_fct[i](cmd, &fd, data);
	if (fd.in > 0)
		close(fd.in);
	if (fd.out > 0)
		close(fd.out);
	return (ret);
}

int	is_built_in(char *s)
{
	const char	*built_in[] = BUILT_IN_LIST;
	int	i;

	i = 0;
	while (built_in[i])
	{

		if (ft_strcmp(built_in[i], s) == 0)
			return (1);
		i++;
	}
	return (0);
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
		if (args[l][0] != '-')
			break ;
		i = 1;
		while (args[l][i])
		{
			check = find_char(args[l][i], options);
			if (check == -1)
			{
				if (invalid)
				{
					if (args[l][i])
						*invalid = args[l][i];
					else
						*invalid = '-';					
				}
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