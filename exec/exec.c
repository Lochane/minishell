
#include "../minishell.h"

long ft_atol(char *nbr, char *check)
{
	int				sign;
	unsigned long	nb;
	unsigned long	max;

	nb = 0;
	max = (unsigned long) LONG_MAX + 3;
	sign = 0;
	while ((nbr && *nbr == 32) || (*nbr <= 13 && *nbr >= 9))
		nbr++;
	if (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			sign = 1;
		nbr++;
	}
	while (*nbr && *nbr <= '9' && *nbr >= '0' && nb < max)
		nb = nb * 10 + *nbr++ - '0';
	if ((nb > max - 3 && !sign) || (nb > max - 2 && sign) || (*nbr >= '0' && *nbr <= '9'))
		*check = 1;
	else if (*nbr != 0)
		*check = 2;
	//1 si overflow 2 si non numeric? 0 si ok
	if (sign)
		nb *= -1;
	return (sign);
}

int	ft_strcmp(const char *s, const char *s1)
{
	int	i;
	
	i = 0;
	if (!s || !s1)
		return (s - s1);
	while (s[i] && s[i] == s1[i])
		i++;
	return (s[i] - s1[i]);
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
	while (s1 && s1[i])
	{
		s3[i] = s1[i];
		i++;
	}
	if (c)
		s3[i++] = c;
	while (s2 && s2[j])
		s3[i++] = s2[j++];
	s3[i] = 0;
	return (s3);
}

void	failure_critic(int res)
{
	//(void) res;
	//test de print strerror join avec "minishell :" via ft_join
	//prendre en parametre retour d'erreur
	//dprintf(2,"errno == %d\n", errno);
	exit(res);
}

void	ft_error(char *message, char *message2, int info)
{
	char	*str;
	char	*str2;
	char	*err;

	str2 = NULL;
	str = ft_join("minishell: ", message, 0);//protgeger alloc
	if (!message2 && !info)
		str2 = ft_join(str, strerror(errno), ' ');//proteger les allocs
	else if (message && info)
	{
		err = ft_join(message2, strerror(errno), 0);//proteger allocs
		str2 = ft_join(str, err, ' ');//proteger les allocs
		free(err);
	}
	else if (message)
		str2 = ft_join(str, message2, ' ');//proteger les allocs
	free(str);
	str = ft_join(str2, NULL, '\n');
	free(str2);
	write(2, str, ft_strlen(str));
	free(str);
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

char	*check_access(char *cmd, char **path)
{
	int		i;
	char	*pathed;
	//char	err[2048];

	i = 0;
	if (!cmd)
		return (NULL);//free_and_exit();
	//if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/') || \
	//(cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/'))
	if (cmd[0] == '/' && !cmd[1])
	{
		write(2, "minishell: /: Is a directory\n", 29);
		return (NULL);
	}
	if (!check_path(cmd))
	{
		if (!access(cmd, F_OK | X_OK))
			return (ft_strdup(cmd));
		ft_error(cmd, NULL, 0);
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
			//else heredoc
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

int	ft_var_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while ((s1[i] && s1[i] != '=') && s1[i] == s2[i])
		i++;
	if ((!s1[i] || s1[i] == '=') && s2[i] == '=')
		return (0);
	else
		return (1);
}

char	*ft_get_env(char *var, t_lst *env, t_lst **lst)
{
	t_lst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_var_cmp(var, tmp->data))
		{
			if (lst)
				*lst = tmp;
			return (&tmp->data[ft_strlen(var) + 1]);
		}
		tmp = tmp->next;
	}
	if (lst)
		*lst = NULL;
	return (NULL);
}

int remove_lst(t_lst **lst, char *name)
{
	(void) lst;
	t_lst	*tmp;
	t_lst	*prev;

	if (!*lst)
		return (0);
	prev = *lst;
	ft_get_env(name, *lst, &tmp);
	if (!tmp)
		return (0);
	while (prev && prev->next != tmp)
		prev = prev->next;
	prev->next = tmp->next;
	free(tmp->data);
	free(tmp);
	return (1);
}

int	print_env(t_cmd *cmd, t_fd fd, t_data *data)
{
	int	final_fd;
	char	*str;
	t_lst	*tmp;

	if (fd.out > 0)
		final_fd = fd.out;
	(void) cmd;
	(void) data;
	tmp = data->env;
	while (tmp)
	{
		str = ft_join(tmp->data, NULL, '\n');
		//proteger echec allocation
		if (write(final_fd, str, ft_strlen(str)) == -1)
		{
			ft_error(cmd->cmd, "write error: ", 1);
			return (125);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	do_echo(t_cmd *cmd, t_fd fd, t_data *data)
{
	(void) cmd;
	(void) fd;
	(void) data;
	int	i;
	int	ret;
	int	n;
	int	final_fd;

	i = 0;
	ret = 0;
	n = 0;
	final_fd = 1;
	if (fd.out > 0)
		final_fd = fd.out;
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
	while (cmd->arg[i])
	{
		//buffiuriser le print
		i++;
	}
	//set le \n si option
	return (0);
}

int	do_cd(t_cmd *cmd, t_fd fd, t_data *data)
{
	t_lst *pwd;
	t_lst *oldpwd;
	
	
	ft_get_env("PWD", data->env, &pwd);
	ft_get_env("OLDPWD", data->env, &oldpwd);
	if (cmd->arg)
	{
		if(cmd->arg[1])
		{
			printf("too many argument\n"); // TODO sortie d'erreur
			return(0);
		}
		if(chdir(cmd->arg[0]))
		{
			printf("No such file\n"); // TODO sortie d'erreur
			return(0);
		}
		if(oldpwd && pwd)
		{
			free(oldpwd->data);
			oldpwd->data = pwd->data;
		}
	}
	else
		printf("No arguments\n"); // TODO sortie d'erreur
	(void) fd;
	(void) data;
	return (0);
}

int	check_var(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	do_export(t_cmd *cmd, t_fd fd, t_data *data)
{
	(void) cmd;
	(void) fd;
	t_lst	*var;
	t_lst	*new;
	int		i;

	//a faire en bouvle tant qu'il y a des args
	if (cmd->arg)
	{
		i = 0;
		while (cmd->arg[i])
		{
			if (check_var(cmd->arg[i]))
			{
				ft_get_env(cmd->arg[i], data->env, &var);
				if (!var)
				{
					new = ft_new_lst(cmd->arg[i]);//proteger le malloc
					ft_add_back(&data->env, new);
				}
				else
				{
					free(var->data);
					var->data = ft_strdup(cmd->arg[i]);
				}
			}
			i++;
		}
	}
	return (0);
}

int	do_unset(t_cmd *cmd, t_fd fd, t_data *data)
{
	(void) cmd;
	(void) fd;
	(void) data;
	int	i;

	if (cmd->arg)
	{
		i = 0;
		while (cmd->arg[i])
		{
			remove_lst(&data->env, cmd->arg[i]);//a faire en boucle tant au'il y a des arg
			i++;
		}
	}
	return (0);
}

int	do_exit(t_cmd *cmd, t_fd fd, t_data *data)
{
	(void) cmd;
	(void) fd;
	int		check;
	//long	nb;
	int	i;

	i = 1;
	check = 0;
	//long	nb;
	if (!cmd->arg)
		exit(data->return_value);
	//nb = ft_atol(cmd->arg[0], &check);
	if (check)//check si different retour si nonnumeric ou overflow ou si les 2 juste non numeric
		return (data->return_value);
	//	exit (nb % 130);
	return (0);
}

int	do_pwd(t_cmd *cmd, t_fd fd, t_data *data)
{
	char	*var;
	int		final_fd;
	char	*str;

	final_fd = 1;
	var = ft_get_env("PWD", data->env, NULL);
	if (fd.out > 0)
		final_fd = fd.out;
	if (!var)
	{
		ft_error(cmd->cmd, "PWD not set", 0);
		return (0);
	}
	str = ft_join(var, NULL, '\n');
	//proteger echec allocation
	if (write(final_fd, str, ft_strlen(str)) == -1)
	{
		printf("errno == %d\n", errno);
		//ft_error(cmd->cmd, ": write error: No space left on device");
		ft_error(cmd->cmd, "write error: ", 1);
		free(str);
		return (1);
	}
	free(str);
	return (0);
}

int	do_built_in(t_cmd *cmd, t_data *data)
{
	const char		*built_in_name[] = {"echo", "cd", "pwd", "export", "env","unset", "exit", NULL};
	const fct	built_in_fct[]  = {do_echo, do_cd, do_pwd, do_export, print_env, do_unset, do_exit};
	//faire un tableau de fct built in dans le meme ordre afin de donner la cmd a la fct de i
	int	i;
	t_fd	fd;
	int		ret;

	if (open_redir(cmd->redirection, &fd) == 1)
	{
		if (fd.in > 0)
			close(fd.in);
		if (fd.out > 0)
			close(fd.out);
		return (1);
	}
	i = 0;
	while (built_in_name[i])
	{
		if (ft_strcmp(built_in_name[i], cmd->cmd) == 0)
			break ;
		i++;
	}
	ret = built_in_fct[i](cmd, fd, data);
	if (fd.in > 0)
		close(fd.in);
	if (fd.out > 0)
		close(fd.out);
	return (ret);
}

int	is_built_in(char *s)
{
	const char	*built_in[] = {"echo", "cd", "pwd", "export", "env","unset", "exit", NULL};
	int	i;

	i = 0;
	while (built_in[i])
	{
		if (ft_strcmp(built_in[i], s) == 0)
			return (1);
		i++;
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
		do_built_in(cmd_lst, data);
		exit (0);
	}
	env = lst_to_tab(data->env);
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
		return (do_built_in(cmd, data));
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
