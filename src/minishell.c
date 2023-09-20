/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/13 17:15:08 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
		strerror(CTRL_C);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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
	intercept_sig();
	printf("\033[H\033[J");
	//data.env = tab_to_list(envp);
	while (1)
	{
		manage_data(&data, 0);
		data.args = readline(PROMPT);
		if (data.args)
		{
			if (history(data.args) == 0)
			{
				if (check_syntax(data.args) == 0)
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
			printf(RED"Exit\n"RESET);
			break ;
		}
		//print_cmds(dta.cmd);
		handle_cmds(data.cmd, envp);
		manage_data(&data, 0);
	}
	return (0);
}
