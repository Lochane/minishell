/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/26 23:52:33 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

unsigned char	g_g;

void	free_redirection(t_dir *redir)
{
	t_dir	*tmp_dir;
	
	while (redir)
	{
		free(redir->file);
		tmp_dir = redir->next;
		if (redir->fd != -1)
			close(redir->fd);
		free(redir);
		redir = tmp_dir;
	}
}

void	manage_data(t_data *data, int allow)
{
	t_cmd	*tmp;

	if (allow == 0)
	{
		data->args = NULL;
		data->cmd = NULL;
	}
	else
	{
		while (data->cmd)
		{
			free_redirection(data->cmd->redirection);
			ft_free_tab(data->cmd->arg, tab_size(data->cmd->arg));
			free(data->cmd->cmd);
			tmp = data->cmd->next;
			free(data->cmd);
			data->cmd = tmp;
		}
		free(data->args);
		data->args = NULL;
		data->cmd = NULL;
	}
}





int	history(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			add_history(str);
			return (0);
		}
		i++;
	}
	return (1);
}


char	*get_line(t_data data)
{
	char	*line;
	int		len;

	if (data.tty == 0)
	{
		line = get_next_line(0);
		if (!line)
			return (NULL);
		len = ft_strlen(line);
		len -= (line[len - 1] == '\n');
		line[len] = 0;
		return (line);
	}	
	else
		return (readline(PROMPT));
}

void	update_shlvl(t_lst **env)
{
	t_lst	*lst;
	char	*content;
	int		value;
	char	shlvl[12];
	
	content = ft_get_env("SHLVL", 5, *env, &lst);
	if (lst)
	{
		value = ft_atoi(content);
		if (value < 0)
			value = 0;
		else
			value +=1;
		if (value >= 1000)
		{
			stack_itoa(shlvl, (unsigned int) value);
			write(1, "minishell: warning: shell level ", 33);
			write(1, shlvl, ft_strlen(shlvl));
			write(1, " too high, resetting to 1\n", 26);//joinpool?
			value = 1;
		}
		stack_itoa(shlvl, value);
		content = ft_join("SHLVL=", shlvl, 0);
		if (!content)
			return (ft_clear_lst(env), fail_malloc());
		free(lst->data);
		lst->data = content;
	}
	else
	{
		content = ft_strdup("SHLVL=1");
		if (!content)
			return (ft_clear_lst(env), fail_malloc());
		lst = ft_new_lst(content);
		if (!lst)
			return (free(content), ft_clear_lst(env), fail_malloc());
		ft_add_back(env, lst);	
	}
}

void	update_path(t_lst **env)
{
	t_lst	*lst;
	char	*content;

	ft_get_env("PATH", 4, *env, &lst);
	content = ft_get_env("PWD", 3, *env, NULL);
	if (!lst)
	{
		content = ft_join(PATH, content, ':');
		lst = ft_new_lst(content);
		if (!lst)
			return (free(content), ft_clear_lst(env));
		ft_add_back(env, lst);
	}
}

void	update_pwd(t_lst **env)
{
	t_lst	*lst;
	char	*content;
	char	*var_name;
	
	ft_get_env("PWD", 3, *env, &lst);
	content = getcwd(NULL, 0);
	var_name = ft_join("PWD=", content, 0);
	if (!var_name)
		return (ft_clear_lst(env), fail_malloc());
	free(content);
	if (lst)
	{
		free(lst->data);
		lst->data = var_name;
	}
	else
	{
		lst = ft_new_lst(var_name);
		if (!lst)
			return (free(var_name), ft_clear_lst(env));
		ft_add_back(env, lst);	
	}
}

void	update_env(t_lst **env)
{
	update_pwd(env);
	if (!env)
		return ;
	update_path(env);
	if (!env)
		return ;
	update_shlvl(env);
}

t_lst	*init_env(char **env)
{
	t_lst	*lst;
	
	lst = tab_to_list(env);
	update_env(&lst);
	return (lst);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argv;
	if (argc != 1)
	{
		write(2, "Error:\nThis program don't take arguments\n", 42);
		exit(0);
	}
	data.tty = isatty(0);
	//if (data.tty)
	//	printf("\033[H\033[J\n");
	g_g = 0;
	data.new_line = 0;
	data.return_value = 0;
	data.fd = dup(0);
	if (data.fd == -1)
		return (perror("dup"), errno);
	data.env = init_env(envp);
	if (envp[0] && !data.env)
		return (ft_putstr_fd("echec d'allocation\n", 2), errno);
	while (1)
	{
		intercept_sig();
		manage_data(&data, 0);
		data.args = get_line(data);
		if (g_g == 130)
			handle_sig(&data);
		else
		{
			if (data.args)
			{
				if (history(data.args) == 0)
				{
					if (check_syntax(data.args, &data) == 0)
					{
						if (!set_cmd(&data))
						{
							if (g_g == 130)
							{
								if (data.new_line)
									write(1, "\n", 1);
								handle_sig(&data);
							}
							manage_data(&data, 1);
						}
					}
				}
			}
			else
			{
				manage_data(&data, 1);
				do_exit(data.cmd, NULL, &data);
				break ;
			}
			if (data.cmd)
				expansion(&data);
			if (data.cmd && data.return_value != 12)
				data.return_value = handle_cmds(data.cmd, &data);
			manage_data(&data, 1);
		}
	}
	return (0);
}
