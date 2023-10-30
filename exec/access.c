/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 21:17:37 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 22:12:37 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (&env[i][5]);
		i++;
	}
	return (NULL);
}

int	check_path(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (0);
	if (cmd[0] == '.')
		return (0);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

char	*check_all_path(char **pathed, char *cmd, char **path)
{
	int	i;

	i = 0;
	while (path && path[i])
	{
		*pathed = ft_join(path[i], cmd, '/');
		if (!*pathed)
			return (fail_malloc(), NULL);
		if (!access(*pathed, F_OK | X_OK))
		{
			if (!is_dir(*pathed))
				return (if_dir(cmd));
			return (*pathed);
		}
		free(*pathed);
		*pathed = NULL;
		i++;
	}
	ft_error(cmd, ":command not found", 0);
	return (NULL);
}

char	*check_access(char *cmd, char **path)
{
	char	*pathed;

	if (!cmd)
		return (NULL);
	if (!cmd[0])
		return (ft_error("''", ": command not found", 0), NULL);
	if (!path || !check_path(cmd))
	{
		if (!access(cmd, F_OK | X_OK))
		{
			if (!is_dir(cmd))
				return (if_dir(cmd));
			return (ft_strdup(cmd));
		}
		ft_error(cmd, NULL, 0);
		return (NULL);
	}
	return (check_all_path(&pathed, cmd, path));
}
