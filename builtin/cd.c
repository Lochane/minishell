/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/29 01:46:38 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_pwd(t_data *data, t_cd *cd)
{
	cd->oldpwdpath = ft_join("OLDPWD=", cd->oldpwdpath, 0);
	if (!cd->oldpwdpath)
		return (free(cd->pwdpath), fail_malloc(), errno);
	if (cd->oldpwd)
	{
		free(cd->oldpwd->data);
		cd->oldpwd->data = cd->oldpwdpath;
	}
	else
	{
		cd->oldpwd = ft_new_lst(cd->oldpwdpath);
		if (!cd->oldpwd)
			return (free(cd->pwdpath), free(cd->oldpwdpath), \
			fail_malloc(), errno);
		ft_add_back(&data->env, cd->oldpwd);
	}
	free(cd->pwd->data);
	cd->pwd->data = ft_join("PWD=", cd->pwdpath, 0);
	if (!cd->pwd->data)
		return (free(cd->pwdpath), fail_malloc(), errno);
	free(cd->pwdpath);
	return (0);
}

int	if_nopwd(t_data *data, t_cd *cd)
{
	remove_lst(&data->env, "OLDPWD");
	cd->pwd = ft_new_lst(ft_join("PWD=", cd->pwdpath, 0));
	if (!cd->pwd)
		return (free(cd->pwdpath), fail_malloc(), errno);
	ft_add_back(&data->env, cd->pwd);
	free(cd->pwdpath);
	return (0);
}

int	do_check_option(t_cmd *cmd, t_cd *cd)
{
	cd->check = check_options(cmd->arg, CD_OPTION, cd->option, &cd->invalid);
	if (cd->invalid)
	{
		error_option(cmd->cmd, cd->invalid);
		write(2, CD_USAGE, ft_strlen(CD_USAGE));
		return (2);
	}
	return (0);
}

void	init_cd(t_cd *cd, t_data *data, t_fd *fd)
{
	(void) fd;
	cd->invalid = 0;
	cd->pwdpath = ft_get_env("PWD", 3, data->env, &cd->pwd);
	cd->arg = ft_get_env("OLDPWD", 6, data->env, &cd->oldpwd);
	cd->oldpwdpath = cd->pwdpath;
}

int	do_cd(t_cmd *cmd, t_fd *fd, t_data *data)
{
	t_cd	cd;

	init_cd(&cd, data, fd);
	if (cmd->arg)
	{
		if (do_check_option(cmd, &cd))
			return (2);
		if (cmd->arg[1])
			return (write(2, "minishell: cd: too many argument\n", 34), 0);
		if ((!(cmd->arg[0][0] == '-' && cmd->arg[0][1] == 0)))
			return (write(2, "minishell: cd: OLDPWD not set\n", 31), 1);
		if (!cd.arg)
			cd.arg = cmd->arg[0];
		if (chdir(cd.arg))
			return (write(2, "No such file\n", 14), 1);
		cd.pwdpath = getcwd(NULL, 0);
		if (!cd.pwdpath)
			return (fail_malloc(), 12);
		if (!cd.pwd)
			return (if_nopwd(data, &cd));
		else
			return (if_pwd(data, &cd));
	}
	return (write(2, "No arguments\n", 14), 0);
}
