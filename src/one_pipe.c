/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:23:02 by uaupetit          #+#    #+#             */
/*   Updated: 2023/07/06 17:36:12 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
char	*find_path(char *cmd, char **envp)
{
	int		j;
	char	**paths;
	char	*path;

	j = 0;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (envp[j] && strncmp(envp[j], "PATH=", 5) != 0)
		j++;
	if (envp[j] == NULL)
		return (NULL);
	paths = ft_split(envp[j] + 5, ':');
	if (!paths)
		return (NULL);
	path = search_paths(cmd, paths);
	free_split(paths);
	return (path);
}

char	*search_paths(char *cmd, char **paths)
{
	int		i;
	char	*path;
	char	*part_path;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		if (access(path, F_OK) == 0)
		{
			free(part_path);
			return (path);
		}
		free(part_path);
		free(path);
		i++;
	}
	return (NULL);
}*/

void	child1_process(t_data *data, int *pipe_fd)
{
	int	fd1;
	fd1 = open(data->cmd->in, O_RDONLY);
	if (fd1 < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
		perror("");
	if (dup2(fd1, STDIN_FILENO) < 0)
		perror("");
	close(pipe_fd[0]);
	close(fd1);
	close(pipe_fd[1]);
	execute_sc(data);
}

void	child2_process(t_data *data, int *pipe_fd)
{
	int		fd2;

	fd2 = open(data->cmd->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd2 < 0)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
		perror("");
	if (dup2(fd2, STDOUT_FILENO) == -1)
		perror("");
	close(pipe_fd[1]);
	close(fd2);
	close(pipe_fd[0]);
	execute_sc(data);
}

void	pipex(t_data *data)
{
	int		pipe_fd[2];
	pid_t	id1;
	pid_t	id2;
	int		status;

	pipe(pipe_fd);
	id1 = fork();
	if (id1 == -1)
		return (perror("Fork failed: "));
	if (id1 == 0)
	{
		child1_process(data, pipe_fd);
		exit(EXIT_SUCCESS);
	}
	printf("ok\n");
	id2 = fork();
	if (id2 == -1)
		return (perror("Fork failed: "));
	if (id2 == 0)
	{
		child2_process(data, pipe_fd);
		exit(EXIT_SUCCESS);
	}
	printf("ok2\n");
	ft_close(pipe_fd);
	waitpid(id1, NULL, 0);
	waitpid(id2, &status, 0);
}

void	ft_close(int pipe_fd[])
{
	close(pipe_fd[1]);
	close(pipe_fd[0]);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}