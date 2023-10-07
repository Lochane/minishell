/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/07 16:44:06 by lsouquie         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 1 || argv[1])
	{
		printf("Error:\nThis program don't take arguments\n");
		exit(0);
	}
	g_g = 0;
	data.fd = dup(0);
	data.new_line = 0;
	data.return_value = 0;
	intercept_sig();
	printf("\033[H\033[J");
	data.env = tab_to_list(envp);
	//if (!init_here_doc(&data.here_doc))
	//	return (0);//free l'env
	//modifier pour proteger l'erreur de malloc peut etre null si pas d'env
	while (1)
	{
		manage_data(&data, 0);
		data.args = readline(PROMPT);
		if (g_g == 130)
		{
			dup(data.fd);
			g_g = CTRL_C;
			data.return_value = g_g;
			g_g = 0;
			if (!data.new_line++)
				write(1, "\n", 1);
		}
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
							manage_data(&data, 1);
							break ;
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
