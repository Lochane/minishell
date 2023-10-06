/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/06 19:25:19 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



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
		if (oldpwd && pwd)
		{
			free(oldpwd->data);
			oldpwd->data = ft_join("OLDPWD=", pwdpath, 0);//proteger allloc cas ou ca peut etre null et normal?
			free(pwd->data);
			pwdpath = getcwd(NULL, 0);
			pwd->data = ft_join("PWD=", pwdpath, 0);
			free(pwdpath);
		}
	}
	else
		printf("No arguments\n"); // TODO sortie d'erreur
	return (0);
}