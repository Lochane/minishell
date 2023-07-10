/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/07/10 16:24:40 by lsouquie         ###   ########.fr       */
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
	struct	sigaction	ca;

	if (argc != 1 || argv[1])
	{
		printf("Error:\nThis program don't take arguments\n");
		exit(0);
	}
	ca.sa_sigaction = sig_handler;
	ca.sa_flags = 0;
	sigemptyset(&ca.sa_mask);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGINT, &ca, NULL);
	while (1)
	{
		data.args = readline(PROMPT);
		if (data.args)
		{
			if (history(data.args) == 0)
			{
				if (check_syntax(data.args) == 0)
					set_cmd(&data);
			}
		}
		else
			break ;
		/*data.env_lst = env_lst(envp, &data);
		copy_env_to_data(&data);
		path_init(&data);
		execute_cmd(&data);*/
		int i = 1;
		while (data.cmd)
		{
			printf("****maillon : %d *****\ncmd = %s\nin = %s\nout = %s\n **********\n", i, data.cmd->cmd, data.cmd->in, data.cmd->out);
			data.cmd = data.cmd->next;
			i++;
		}
		/*int i = 0;
		while (data.envcpy[i])
		{
			printf("%s\n", data.envcpy[i]);
			i++;
		}*/
	}
	return (0);
}
