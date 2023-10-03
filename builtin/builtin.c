/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/03 12:01:18 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_var_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s1[i] != '=') && s1[i] == s2[i])
		i++;
	if ((!s1[i] || s1[i] == '=') && s2[i] == '=')
		return (0);
	else
		return (1);
}

char	*ft_get_env(char *var, t_lst *env, t_lst **lst)
{
	t_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_var_cmp(var, tmp->data))
		{
			if (lst)
				*lst = tmp;
			return (&tmp->data[ft_strlen(var) + 1]);
		}
		tmp = tmp->next;
	}
	if (lst)
		*lst = NULL;
	return (NULL);
}

int	do_built_in(t_cmd *cmd, t_data *data)
{
	const char		*built_in_name[] = {"echo", "cd", "pwd", "export", "env","unset", "exit", NULL};
	const fct	built_in_fct[]  = {do_echo, do_cd, do_pwd, do_export, print_env, do_unset, do_exit};
	int		i;
	t_fd	fd;
	int		ret;
	//faire un tableau de fct built in dans le meme ordre afin de donner la cmd a la fct de i

	if (open_redir(cmd->redirection, &fd) == 1)
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
	ret = built_in_fct[i](cmd, fd, data);
	if (fd.in > 0)
		close(fd.in);
	if (fd.out > 0)
		close(fd.out);
	return (ret);
}

int	is_built_in(char *s)
{
	const char	*built_in[] = {"echo", "cd", "pwd", "export", "env","unset", "exit", NULL};
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