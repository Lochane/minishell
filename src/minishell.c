/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/08 16:28:18 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	sig_handler(int signum, siginfo_t *info, void *content)
{
	if (signum == SIGINT)
	{
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

	ca.sa_sigaction = sig_handler;
	ca.sa_flags = 0;
	sigemptyset(&ca.sa_mask);
	signal(SIGQUIT, SIG_IGN);
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
	while (1)
	{
		data.args = readline(PROMPT);
		if (data.args)
		{
			if (history(data.args) == 0)
			{
				if (check_syntax(data.args) == 0)
				{
					if (!set_cmd(&data))
					{
						// TODO clean tout
						break ;
					}
				}
			}
		}
		else
			break ;
		int i = 0;
		while (data.cmd)
		{
			printf("****maillon*****\ncmd = %s\n", data.cmd->cmd);
			// while (data.cmd->arg[i])
			// {
			// 	printf("arg = %s\n", data.cmd->arg[i]);
			// 	i++;
			// }
			while (data.cmd->redirection)
			{
				printf("redirection = %s\n", data.cmd->redirection->file);
				data.cmd->redirection = data.cmd->redirection->next;
			}
			printf("**********\n");
			data.cmd = data.cmd->next;
		}
	}
	return (0);
}
