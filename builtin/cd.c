/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/09 11:39:31 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"



int	do_cd(t_cmd *cmd, t_fd *fd, t_data *data)
{
	t_lst	*pwd;
	t_lst	*oldpwd;
	//char	*oldpwdpath;
	char	*pwdpath;

	(void) fd;
	(void)cmd;
	pwdpath = ft_get_env("PWD", 3, data->env, &pwd);
	ft_get_env("OLDPWD", 6, data->env, &oldpwd);
	/*if (cmd->arg)
	{
		if (cmd->arg[1])
			return ((2, "too many argument\n", 19), 0);
		if (chdir(cmd->arg[0]))
			return (write(2, "No such file\n", 14), 0);
		pwdpath = getcwd(NULL, 0);
		if (pwd)
		{
			oldpwdpath = ft_join("OLDPWD=", pwd->data, 0);
			if (!oldpwdpath)
				return (fail_malloc(), errno);//free pwdpath
			free(pwd->data);
		}
		pwd->data = ft_join("PWD=", pwdpath, 0);
		if (oldpwd)
			free(oldpwd->data);

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
			ft_add_back(&data->env, oldpwd);
		}
		free(pwdpath);
		free(oldpwdpath);
	}
	else
		printf("No arguments\n"); // TODO sortie d'erreur*/
	return (0);
}