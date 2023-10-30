/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:17:46 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 21:41:14 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_dir(const char *fileName)
{
	struct stat	path;

	stat(fileName, &path);
	return (S_ISREG(path.st_mode));
}

char	*if_dir(char *cmd)
{
	ft_error(cmd, ": Is a directory", 0);
	g_g = 126;
	return (NULL);
}
