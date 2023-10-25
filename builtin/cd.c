/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/24 23:12:21 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_cd(t_cmd *cmd, t_fd *fd, t_data *data)
{
	t_lst	*pwd;
	t_lst	*oldpwd;
	char	*oldpwdpath;
	char	*pwdpath;
	char	option[0];
	int		check;
	char	buffer[36];
	char	invalid;
	
	(void) fd;
	(void)cmd;
	invalid = 0;
	pwdpath = ft_get_env("PWD", 3, data->env, &pwd);
	ft_get_env("OLDPWD", 6, data->env, &oldpwd);
	if (cmd->arg)
	{
		check = check_options(cmd->arg ,CD_OPTION, option, &invalid);
		if (check != 0 || cmd->arg[0][0] == '-')
		{
			ft_strlcpy(buffer, "minishell: cd: -o: invalid option\n", 35);
			buffer[16] = cmd->arg[0][1];	
			write(2, buffer, 35);
			return (2);
		}
		if (cmd->arg[1])
			return (write(2, "minishell: cd: too many argument\n", 34), 0);
		if (chdir(cmd->arg[0]))
			return (write(2, "No such file\n", 14), 0);
		pwdpath = getcwd(NULL, 0);
		if (pwd)
		{
			if (oldpwd)
			{
				oldpwdpath = ft_join("OLDPWD=", pwdpath, 0);
				if (!oldpwdpath)
					return (free(pwdpath), fail_malloc(), errno);
				free(oldpwd->data);
			}
			free(pwd->data);
			pwd->data = ft_join("PWD=", pwdpath, 0);
			if (oldpwd && oldpwdpath)
				oldpwd->data = oldpwdpath;
		}
		if (!pwd)
		{
			pwd = ft_new_lst(ft_join("PWD=", pwdpath, 0));
			if (!pwd)
				return (free(pwdpath), fail_malloc(), errno);
			ft_add_back(&data->env, pwd);
		}
		free(pwdpath);
	}
	else
		write(2, "No arguments\n", 14);
	return (0);
}