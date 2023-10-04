
#include "../minishell.h"

void	failure_critic(int res)
{
	//(void) res;
	//test de print strerror join avec "minishell :" via ft_join
	//prendre en parametre retour d'erreur
	//dprintf(2,"errno == %d\n", errno);
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
	//char	err[2048];

	i = 0;
	if (!cmd)
		return (NULL);//free_and_exit();
	if (!check_path(cmd))
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
			if (!is_dir(pathed))
			{
				ft_error(pathed,"Is a directory", 0);
				return (NULL);
			}
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
	int		i;

	tmp = redir;
	i = 0;
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


void	exec(t_cmd *cmd_lst, int built_in , t_data *data)
{
	char	**path;
	char	**cmd;
	char	*pathed;
	t_cmd	*tmp;
	t_fd	fd;
	char **env;

	if (dup_pipe(cmd_lst) == 1)
		failure_critic(1);
	if (open_redir(cmd_lst->redirection, &fd) == 1)
	{
		if (fd.in > 0)
			close(fd.in);
		if (fd.out > 0)
			close(fd.out);
		failure_critic(1);
	}
	if (dup_redir(fd) == 1)
		failure_critic(1);
	if (fd.in > 0)
		close(fd.in);
	if (fd.out > 0)
		close(fd.out);
	//if (env->infile.fd == -1 && i == 0)
	//	handle_invalide_in(env);
	//if (env->outfile.fd == -1 && i == env->nb_cmd -1)
	//	handle_invalid_out(env);
	built_in = is_built_in(cmd_lst->cmd);
	if (built_in)
	{
		do_built_in(cmd_lst, data, 0);
		exit (0);
	}
	env = lst_to_tab(data->env);//proteger malloc
	path = ft_split(get_path(env), ':');
	cmd = join_cmd(cmd_lst->cmd, cmd_lst->arg);
	if (!cmd)
	{
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		exit(errno);
	}
	//	fail_cmd(env, cmd, path);
	pathed = check_access(cmd[0], path);
	if (!pathed)
		failure_critic(127);//fail_cmd();
	//dup_all();
	//close_all(cmd, i);
	tmp = cmd_lst;
	while (tmp)
	{
		if (tmp->pipe != -1)
			close(tmp->pipe);
		if (tmp->prev_pipe != -1)
			close(tmp->prev_pipe);
		tmp = tmp->next;
	}
	execve(pathed, cmd, env);
	ft_free_tab(path, tab_size(path));
	ft_free_tab(cmd, tab_size(cmd));
	free(pathed);
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

int	get_status(int *status)
{
	int	res;

	res = 0;
	if (WIFEXITED(*status))
		res = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		res = (WTERMSIG(*status));
	return (res);
}

int	waiting(t_cmd *cmd, int nb_cmd)
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
				res = get_status(&status);
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
	int		prev_pipe;
	int		built_in;
	int		nb_cmd;

	tmp = cmd;
	i = 0;
	prev_pipe = -1;
	pip[0] = -1;
	pip[1] = -1;
	nb_cmd = cmd_size(cmd);
	modif_cmd(tmp);
	built_in = is_built_in(cmd->cmd);
	if (built_in && nb_cmd == 1)
		return (do_built_in(cmd, data, 1));
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
			exec(tmp , built_in, data);
		i++;
		if (tmp->pipe != -1)
			close(tmp->pipe);
		if (tmp->prev_pipe != -1)
			close(tmp->prev_pipe);
		tmp = tmp->next;
	}
	return (waiting(cmd, cmd_size(cmd)));
}
