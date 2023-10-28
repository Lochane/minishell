/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/28 23:39:52 by madaguen         ###   ########.fr       */
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

typedef struct s_echo
{
	int		i;
	int		ret;
	int		final_fd;
	char	*stash;
	char	opt[1];
}			t_echo;

void	init_echo(t_echo *echo)
{
	echo->i = 0;
	echo->ret = 0;
	echo->opt[0] = 0;
	echo->final_fd = 1;
}

int	do_echo(t_cmd *cmd, t_fd *fd, t_data *data)
{
	t_echo	echo;

	(void) fd;
	(void)data;
	init_echo(&echo);
	if (fd->out > 0)
		echo.final_fd = fd->out;
	if (!cmd->arg)
	{
		if (write(echo.final_fd, "\n", 1) == -1)
		{
			echo.ret = 1;
			ft_error(cmd->cmd, "write error: ", 1);
		}
		return (echo.ret);
	}
	echo.i = check_options(cmd->arg, ECHO_OPTIONS, echo.opt, NULL);
	echo.stash = ft_strjoin_pool(tab_size(&cmd->arg[echo.i]), \
	&cmd->arg[echo.i], " ", echo.opt[0]);
	if (!echo.stash)
		return (fail_malloc(), 0);
	write(echo.final_fd, echo.stash, ft_strlen(echo.stash));
	free(echo.stash);
	return (0);
}
