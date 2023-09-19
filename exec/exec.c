
#include "../minishell.h"

void	failure_critic()
{
	exit(0);
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

char	*ft_join(char *s1, char *s2, char c)
{
	int		i;
	int		size;
	char	*s3;
	int		j;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	if (c)
		size = size + 1;
	s3 = malloc(sizeof(char) * size + 1);
	if (!s3)
		return (NULL);
	while (s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	if (c)
		s3[i++] = c;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = 0;
	return (s3);
}

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*pathed;
	//char	err[2048];

	i = 0;
	if (!cmd)
		return (NULL);//free_and_exit();
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || \
	(cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
	{
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
	//	print_error(err, cmd, 1);
		return (NULL);
	}
	while (path && path[i])
	{
		pathed = ft_join(path[i], cmd, '/');
		if (!pathed)
			return (NULL);
		if (!access(pathed, F_OK | X_OK))
			return (pathed);
		free(pathed);
		i++;
	}
	//print_error(err, cmd, 2);
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

void	dup_pipe(t_cmd *cmd)
{
	if (cmd->prev_pipe != -1 && dup2(cmd->prev_pipe, 0) == -1)
	{
		perror("dup2 in");
		failure_critic();
	}
	if ( cmd->pipe != -1 && dup2(cmd->pipe, 1) == -1)
	{
		perror("dup2 out");
		failure_critic();
	}
}

void	exec(t_cmd *cmd_lst, char **env )
{
	char	**path;
	char	**cmd;
	char	*pathed;
	t_cmd	*tmp;

	dup_pipe(cmd_lst);
	//if (env->infile.fd == -1 && i == 0)
	//	handle_invalide_in(env);
	//if (env->outfile.fd == -1 && i == env->nb_cmd -1)
	//	handle_invalid_out(env);
	path = ft_split(get_path(env), ':');
	cmd = join_cmd(cmd_lst->cmd, cmd_lst->arg);
	if (!cmd)
		exit(0);
	//	fail_cmd(env, cmd, path);
	pathed = check_access(cmd[0], path);
	if (!pathed)
		exit(0) ;//fail_cmd();
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
	execve(pathed, cmd, NULL);
	ft_free_tab(path, tab_size(path));
	ft_free_tab(cmd, tab_size(cmd));
	free(pathed);
	failure_critic();
	exit(0);
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

int handle_cmds(t_cmd *cmd, char **env)
{
	int pip[2];
	t_cmd *tmp;
	int		i;
	int		prev_pipe;
	//int		nb_cmd;

	tmp = cmd;
	i = 0;
	prev_pipe = -1;
	pip[0] = -1;
	pip[1] = -1;
	//cnd_cmd = cmd_size;
	modif_cmd(tmp);
	while (tmp)
	{
		if (tmp->next)
			if (pipe(pip) == -1)
				failure_critic();
		if (tmp->next)
			tmp->pipe = pip[1];	
		if (tmp->next)
			tmp->next->prev_pipe = pip[0];
		tmp->pid = fork();
		if (tmp->pid == -1)
		{
			failure_critic();
			return (0);
		}
		else if (tmp->pid == 0)
			exec(tmp , env);
		i++;
		if (tmp->pipe != -1)
			close(tmp->pipe);
		if (tmp->prev_pipe != -1)
			close(tmp->prev_pipe);
		tmp = tmp->next;
	}
	return (waiting(cmd, cmd_size(cmd)));
}
