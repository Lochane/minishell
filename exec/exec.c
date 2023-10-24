
#include "../includes/minishell.h"

void	failure_critic(int res)
{
	exit(res);
}

void	modif_cmd(t_cmd *cmd)
{
	while (cmd)
	{	
		cmd->pipe = -1;
		cmd->prev_pipe = -1;
		cmd->pid = -1;
		cmd = cmd->next;
	}

}

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


int is_dir(const char* fileName)
{
    struct stat path;

    stat(fileName, &path);

    return (S_ISREG(path.st_mode));
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*pathed;

	i = 0;
	if (!cmd)
		return (NULL);//free_and_exit();
	if (!cmd[0])
		return (ft_error("''", "command not found", 0), NULL);
	if (!path || !check_path(cmd))
	{
		if (!access(cmd, F_OK | X_OK))
		{
			if (!is_dir(cmd))
			{
				ft_error(cmd,"Is a directory", 0);
				return (NULL);
			}
			return (ft_strdup(cmd));
		}
		ft_error(cmd, NULL, 0);
		return (NULL);
	}
	while (path && path[i])
	{
		pathed = ft_join(path[i], cmd, '/');
		if (!pathed)
			return (NULL);
		if (!access(pathed, F_OK | X_OK))
		{
			//if (!is_dir(pathed))//je ne sais pas, confirmer par un test
			//{
				//ft_error(cmd,"Is a directory", 0);
			//	return (NULL);
			//}
			return (pathed);
		}
		free(pathed);
		i++;
	}
	ft_error(cmd, "command not found", 0);
	return (NULL);
}

char	**join_cmd(char *cmd, char **arg)
{
	char	**new;
	int		size;
	int		i;

	i = 1;
	if (arg)
		size = tab_size(arg) + 1;
	else
		size = 1;
	new = malloc((size + 1) * sizeof(char *));
	if (!new)
		return (NULL);
	while (i < size)
	{
		new[i] = arg[i - 1];
		i++;
	}
	new[i] = NULL;
	new[0] = cmd;
	return (new);
}

int	dup_pipe(t_cmd *cmd)
{
	if (cmd->prev_pipe != -1 && dup2(cmd->prev_pipe, 0) == -1)
	{
		perror("dup2 pipe in");
		return (1);
	}
	if ( cmd->pipe != -1 && dup2(cmd->pipe, 1) == -1)
	{
		perror("dup2 pipe out");
		return (1);
	}
	return (0);
}

int	dup_redir(t_fd fd)
{
	if (fd.in > 0 && dup2(fd.in , 0) == -1)
	{
		perror("redir dup2 in");
		return (1);
	}
	if (fd.out > 0 && dup2(fd.out, 1) == -1)
	{
		perror("redir dup2 out");
		return (1);
	}
	return (0);
}

int	open_redir(t_dir *redir, t_fd *fd)
{
	t_dir	*tmp;

	tmp = redir;
	fd->in = -2;
	fd->out = -2;
	while (tmp)
	{
		if (tmp->token == GREAT || tmp->token == GREAT_GREAT)
		{
			if (fd->out > 0)
				close(fd->out);
			if (tmp->token == GREAT)
				fd->out = open((const char *)tmp->file, O_TRUNC | O_WRONLY | O_CREAT,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
			else
				fd->out = open((const char *)tmp->file, O_APPEND | O_WRONLY | O_CREAT, \
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
		}
		if (tmp->token == LESS || tmp->token == LESS_LESS)
		{
			if (fd->in > 0)
				close(fd->in);
			if (tmp->token == LESS)
				fd->in = open((const char *)tmp->file, O_RDONLY);
			else
				fd->in = tmp->fd;
		}
		if (tmp->token == DOUBLE)
		{
			if (fd->in > 0)
				close(fd->in);
			if (fd->out > 0)
				close(fd->out);
			fd->out = open((const char *)tmp->file, O_RDONLY | O_CREAT,
				S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);	
			if (fd->out != -1)
			{
				fd->in = fd->out;
				fd->out = 0;
			}
		}
		if (fd->in == -1 || fd->out == -1)
		{
			ft_error(tmp->file, NULL, 0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	free_child(t_fork fork, t_data *data)
{
	if (data->fd > -1)
		close(data->fd);
	data->fd = -1;
	ft_free_tab(fork.path, tab_size(fork.path));
	fork.path = NULL;
	free(fork.cmd);
	fork.cmd = NULL;
	free(fork.pathed);
	rl_clear_history();
	manage_data(data, 1);
	ft_clear_lst(&data->env);
	free(fork.env);
}

void	init_fork(t_fork *fork)
{
	fork->env = NULL;
	fork->path = NULL;
	fork->pathed = NULL;
	fork->cmd = NULL;
}

void	close_pipe_child(t_cmd *cmd)
{
	while (cmd)
	{
		if (cmd->pipe != -1)
			close(cmd->pipe);
		if (cmd->prev_pipe != -1)
			close(cmd->prev_pipe);
		cmd = cmd->next;
	}
}

void	close_redir(t_cmd *cmd)
{
	t_dir *tmp;

	while (cmd)
	{
		tmp = cmd->redirection;
		while (tmp)
		{
			if (tmp->fd != -1)
				close(tmp->fd);
			tmp = tmp->next;
		}
		cmd = cmd->next;
	}
}

void	exec(t_cmd *cmd_lst, t_data *data)
{
	t_fork fork;
	int		built_in;
	
	restore_sig();
	if (data->fd > -1)
		close(data->fd);
	data->fd = -1;
	init_fork(&fork);
	if (dup_pipe(cmd_lst) == 1)
	{
		free_child(fork, data);
		failure_critic(1);
	}
	if (open_redir(cmd_lst->redirection, &fork.fd) == 1)
	{
		close_pipe_child(data->cmd);
		close_redir(data->cmd);
		if (fork.fd.in > 0)
			close(fork.fd.in);
		if (fork.fd.out > 0)
			close(fork.fd.out);
		free_child(fork, data);
		failure_critic(1);
	}
	if (dup_redir(fork.fd) == 1)
	{
		free_child(fork, data);
		close_redir(data->cmd);
		close_pipe_child(data->cmd);
		failure_critic(1);
	}
	close_redir(data->cmd);
	if (fork.fd.in > 0)
		close(fork.fd.in);
	if (fork.fd.out > 0)
		close(fork.fd.out);
	built_in = is_built_in(cmd_lst->cmd);
	if (built_in)
	{
		do_built_in(cmd_lst, data, 0);
		close_pipe_child(data->cmd);
		free_child(fork, data);
		exit (data->return_value);
	}
	fork.env = lst_to_tab(data->env);
	if (!fork.env)
	{
		free_child(fork, data);
		close_pipe_child(data->cmd);
		exit(errno);
	}
	fork.path = ft_split(get_path(fork.env), ':');
	fork.cmd = join_cmd(cmd_lst->cmd, cmd_lst->arg);
	if (!fork.cmd)
	{
		free_child(fork, data);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		exit(errno);
	}
	fork.pathed = check_access(fork.cmd[0], fork.path);
	if (!fork.pathed)
	{
		close_pipe_child(data->cmd);
		free_child(fork, data);
		manage_data(data, 1);
		if (data->fd != -1)
			close(data->fd);
		exit(127);
	}
	close_pipe_child(data->cmd);
	execve(fork.pathed, fork.cmd, fork.env);
	free_child(fork, data);
	failure_critic(0);
}

int	cmd_size(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

int	get_status(int *status, t_data *data)
{
	int	res;

	res = 0;
	if (WIFEXITED(*status))
	{
		res = WEXITSTATUS(*status);
	}
	else if (WIFSIGNALED(*status))
	{
		res = (WTERMSIG(*status));
		res += 128;
		write(1, "\n", 1);
	}
	data->new_line = 0;
	return (res);
}

int	waiting(t_cmd *cmd, int nb_cmd , t_data *data)
{
	pid_t	pid;
	int		res;
	int		status;
	int		pid_waited;
	t_cmd	*tmp;

	pid_waited = 0;
	tmp = cmd;
	while (pid_waited < nb_cmd)
	{
		if (tmp->pid != -1)
			pid = waitpid(tmp->pid, &status, WNOHANG);
		if (pid > 0 && tmp->pid != -1)
		{
			if (!tmp->next)
				res = get_status(&status, data);
			tmp->pid = -1;
			pid_waited++;
		}
		tmp = tmp->next;
		if (!tmp)
			tmp = cmd;
	}
	return (res);
}

int handle_cmds(t_cmd *cmd, t_data *data)
{
	int pip[2];
	t_cmd *tmp;
	int		i;
	int		nb_cmd;

	tmp = cmd;
	i = 0;
	pip[0] = -1;
	pip[1] = -1;
	nb_cmd = cmd_size(cmd);
	modif_cmd(tmp);
	if (nb_cmd == 1 && is_built_in(cmd->cmd))
		return (do_built_in(cmd, data, 1));
	ignore_sig();
	while (tmp)
	{
		if (tmp->next)
			if (pipe(pip) == -1)
				return (1); // erreur creation pipe message fd insuffiant? erno?
		if (tmp->next)
			tmp->pipe = pip[1];	
		if (tmp->next)
			tmp->next->prev_pipe = pip[0];
		tmp->pid = fork();
		if (tmp->pid == -1)
		{
			write(2, "error to create process\n", 24);
			perror("fork : ");
			failure_critic(127);
			return (0);
		}
		else if (tmp->pid == 0)
			exec(tmp , data);
		i++;
		// if (prev_pipe != -1)
		// {
		// 	close(prev_pipe);
		// 	prev_pipe = -1;
		// }
		// if (pip[1] != -1)
		// {
		// 	close(pip[1]);
		// 	pip[1] = -1;
		// }
		// if (pip[0] != -1)
		// {
		// 	prev_pipe = pip[0];
		// 	pip[0] = -1;
		// }
		if (tmp->pipe != -1)
			close(tmp->pipe);
		if (tmp->prev_pipe != -1)
			close(tmp->prev_pipe);
		tmp = tmp->next;
	}
	return (waiting(cmd, cmd_size(cmd), data));
}
