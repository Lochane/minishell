/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/09 14:30:07 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	do_cd(t_cmd *cmd, t_fd *fd, t_data *data)
{
	t_lst	*pwd;
	t_lst	*oldpwd;
	char	*pwdpath;

	(void) fd;
	pwdpath = ft_get_env("PWD", 3, data->env, &pwd);
	ft_get_env("OLDPWD", 6, data->env, &oldpwd);
	if (cmd->arg)
	{
		if (cmd->arg[1])
		{
			printf("too many argument\n"); // TODO sortie d'erreur
			return (0);
		}
		if (chdir(cmd->arg[0]))
		{
			printf("No such file\n"); // TODO sortie d'erreur
			return (0);
		}
		pwdpath = getcwd(NULL, 0);
		if (oldpwd && pwd)
		{
			free(oldpwd->data);
			oldpwd->data = ft_join("OLDPWD=", pwdpath, 0);
			free(pwd->data);
			pwd->data = ft_join("PWD=", pwdpath, 0);
			if (!pwd->data || !oldpwd->data)
				return (fail_malloc(), errno);
		}
		if (!pwd)
		{
			pwd = ft_new_lst(ft_join("PWD=", pwdpath, 0));//bouvcle infinie si on fait env???
			if (!pwd)
				return (fail_malloc(), errno);
			ft_add_back(&data->env, pwd);
		}
		if (!oldpwd)
		{
			oldpwd = ft_new_lst(ft_join("OLDPWD=", pwdpath, 0));
			if (!oldpwd)
				return (fail_malloc(), errno);
			ft_add_back(&data->env, pwd);
		}
		free(pwdpath);
	}
	else
		printf("No arguments\n"); // TODO sortie d'erreur
	return (0);
}