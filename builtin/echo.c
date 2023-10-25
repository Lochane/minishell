/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/24 23:13:09 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	check_option(char **arg)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 1;
// 	while (arg[i])
// 	{
// 		if (arg[i][0] && arg[i][0] == '-')
// 		{
// 			while (arg[i][j])
// 			{
// 				if (arg[i][j] != 'n' || arg[i][j] == '-')
// 					return (i);
// 				j++;
// 			}
// 			i++;
// 		}
// 		else
// 			break ;
// 	}
// 	return(i);
// }

int	do_echo(t_cmd *cmd, t_fd *fd, t_data *data)
{
	int		i;
	int		ret;
	int		final_fd;
	char	*stash;
	char	option[1];

	(void) fd;
	(void)data;
	i = 0;
	ret = 0;
	option[0] = 0;
	final_fd = 1;
	if (fd->out > 0)
		final_fd = fd->out;
	if (!cmd->arg)
	{
		if (write(final_fd, "\n", 1) == -1)
		{
			ret = 1;
			ft_error(cmd->cmd, "write error: ", 1);
		}
		return (ret);
	}
	i = check_options(cmd->arg , ECHO_OPTIONS, option, NULL);
	stash = ft_strjoin_pool(tab_size(&cmd->arg[i]), &cmd->arg[i], " ", option[0]);
	if (!stash)
		return (fail_malloc(), 0);
	write(final_fd, stash, ft_strlen(stash));
	free(stash);
	return (0);
}