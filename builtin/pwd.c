/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:46:02 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/29 01:43:25 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	do_pwd(t_cmd *cmd, t_fd *fd, t_data *data)
{
	t_pwd	pwd;

	(void) data;
	pwd.final_fd = 1;
	pwd.invalid = 0;
	if (cmd->arg)
	{
		pwd.check = check_options(cmd->arg, PWD_OPTION, pwd.opt, &pwd.invalid);
		if (pwd.invalid != 0)
			return (error_option(cmd->cmd, pwd.invalid), \
			write(2, PWD_USAGE, ft_strlen(PWD_USAGE)), 2);
	}
	pwd.var = getcwd(NULL, 0);
	if (!pwd.var)
		return (fail_malloc(), 12);
	if (fd->out > 0)
		pwd.final_fd = fd->out;
	pwd.str = ft_join(pwd.var, NULL, '\n');
	free(pwd.var);
	if (write(pwd.final_fd, pwd.str, ft_strlen(pwd.str)) == -1)
		return (ft_error(cmd->cmd, "write error: ", 1), free(pwd.str), 1);
	free(pwd.str);
	return (0);
}
