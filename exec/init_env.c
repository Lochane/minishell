/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:41:48 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 01:41:51 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_shlvl_util(t_lst *lst, char *content, t_lst **env)
{
	int		value;
	char	shlvl[12];

	value = ft_atoi(content);
	if (value < 0)
		value = 0;
	else
		value += 1;
	if (value >= 1000)
	{
		stack_itoa(shlvl, (unsigned int) value);
		write(2, "minishell: warning: shell level ", 33);
		write(2, shlvl, ft_strlen(shlvl));
		write(2, " too high, resetting to 1\n", 26);
		value = 1;
	}
	stack_itoa(shlvl, value);
	content = ft_join("SHLVL=", shlvl, 0);
	if (!content)
		return (ft_clear_lst(env), fail_malloc());
	free(lst->data);
	lst->data = content;
}

void	update_shlvl(t_lst **env)
{
	t_lst	*lst;
	char	*content;

	content = ft_get_env("SHLVL", 5, *env, &lst);
	if (lst)
		update_shlvl_util(lst, content, env);
	else
	{
		content = ft_strdup("SHLVL=1");
		if (!content)
			return (ft_clear_lst(env), fail_malloc());
		lst = ft_new_lst(content);
		if (!lst)
			return (free(content), ft_clear_lst(env), fail_malloc());
		ft_add_back(env, lst);
	}
}

void	update_path(t_lst **env)
{
	t_lst	*lst;
	char	*content;

	ft_get_env("PATH", 4, *env, &lst);
	content = ft_get_env("PWD", 3, *env, NULL);
	if (!lst)
	{
		content = ft_join(PATH, content, ':');
		lst = ft_new_lst(content);
		if (!lst)
			return (free(content), ft_clear_lst(env));
		ft_add_back(env, lst);
	}
}

void	update_env(t_lst **env)
{
	update_pwd(env);
	if (!env)
		return ;
	update_path(env);
	if (!env)
		return ;
	update_shlvl(env);
}

t_lst	*init_env(char **env)
{
	t_lst	*lst;

	lst = tab_to_list(env);
	update_env(&lst);
	return (lst);
}
