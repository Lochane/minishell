/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/07 22:55:42 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned char	g_g;

void	manage_data(t_data *data, int allow)
{
	if (allow == 0)
	{
		data->args = NULL;
		data->cmd = NULL;
	}
	else
	{
		while (data->cmd)
		{
			while (data->cmd->redirection)
			{
				free(data->cmd->redirection->file);
				free(data->cmd->redirection);
				if (data->cmd->redirection->fd != -1)
					close(data->cmd->redirection->fd);
				data->cmd->redirection = data->cmd->redirection->next;
			}
			ft_free_tab(data->cmd->arg, tab_size(data->cmd->arg));
			free(data->cmd->cmd);
			free(data->cmd);
			data->cmd = data->cmd->next;
		}
		data->args = NULL;
		data->cmd = NULL;
	}
}

void	sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		close(0);
		g_g = CTRL_C;
		//rl_on_new_line();
		//rl_replace_line("", 0);
	}
	else
		return ;
}

void	sig_handler_exec_loop(int signum)
{
	(void) signum;
}

void	restore_sig(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_IGN);
}

void	intercept_sig(void)
{
	struct sigaction	ca;

	ca.sa_handler = sig_handler;
	ca.sa_flags = 0;
	sigemptyset(&ca.sa_mask);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	sigaction(SIGINT, &ca, NULL);
}

void	ignore_sig(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
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

void	handle_sig(t_data *data)
{
	dup2(data->fd, 0);
	data->return_value = g_g;
	g_g = 0;
	if (!data->new_line++)
		write(1, "\n", 1);
}

char	*get_line(t_data data)
{
	char	*line;
	int		len;
	
	if (data.tty == 0)
	{
		line = get_next_line(0);
		len = ft_strlen(line);
		len -= (line[len - 1] == '\n');
		line[len] = 0;
		return (line);
	}	
	else
		return (readline(PROMPT));
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
	{
		printf("Error:\nThis program don't take arguments\n");
		exit(0);
	}
	data.tty = isatty(0);
	if (data.tty)
		printf("\033[H\033[J");
	g_g = 0;
	data.new_line = 0;
	data.return_value = 0;
	data.env = tab_to_list(envp);
	//if (!init_here_doc(&data.here_doc))
	//	return (0);//free l'env
	//modifier pour proteger l'erreur de malloc peut etre null si pas d'env
	data.fd = dup(0);
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
							printf("MMMM?\n");
							if (g_g == 130)
							{
								handle_sig(&data);
								data.new_line = 0;
							}	
							manage_data(&data, 1);
							printf("??\n");
							//break ;
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
			expansion(&data);
			if (data.cmd)
					data.return_value = handle_cmds(data.cmd, &data);
			manage_data(&data, 0);
		}
	}
	return (0);
}
