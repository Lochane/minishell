/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:42:40 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/06 19:27:11 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(char **arg)
{
	int i;
	int j;

	i = 0;
	j = 1;
	while (arg[i])
	{
		if (arg[i][0] && arg[i][0] == '-')
		{
			while (arg[i][j])
			{
				if (arg[i][j] != 'n')
					return (i);
				j++;
			}
			i++;
		}
		else
			break ;
	}
	return(i);
}

int	do_echo(t_cmd *cmd, t_fd *fd, t_data *data)
{
	(void) fd;
	(void)data;
	int		i;
	int		ret;
	int		n;
	int		final_fd;
	char	*stash;

	i = 0;
	ret = 0;
	n = 0;
	final_fd = 1;
	if (fd->out > 0)
		final_fd = fd->out;
	//check -n
	if (!cmd->arg)
	{
		if (write(final_fd, "\n", 1) == -1)
		{
			ret = 1;//check bonne valeur
			ft_error(cmd->cmd, "write error: ", 1);
		}
		return (ret);
	}	
	i = check_option(cmd->arg);
	stash = ft_strjoin_pool(tab_size(&cmd->arg[i]), &cmd->arg[i], " ", i);
	if (!stash)
		return (0); // TODOO Erreur malloc
	write(final_fd, stash, ft_strlen(stash));
	return (0);
}