/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 01:40:24 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 01:41:07 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_pwd(t_lst **env)
{
	t_lst	*lst;
	char	*content;
	char	*var_name;

	ft_get_env("PWD", 3, *env, &lst);
	content = getcwd(NULL, 0);
	var_name = ft_join("PWD=", content, 0);
	if (!var_name)
		return (ft_clear_lst(env), fail_malloc());
	free(content);
	if (lst)
	{
		free(lst->data);
		lst->data = var_name;
	}
	else
	{
		lst = ft_new_lst(var_name);
		if (!lst)
			return (free(var_name), ft_clear_lst(env));
		ft_add_back(env, lst);
	}
}
