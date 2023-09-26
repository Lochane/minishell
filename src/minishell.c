/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/09/26 19:24:42 by madaguen         ###   ########.fr       */
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
	data.return_value = 0;
	intercept_sig();
	printf("\033[H\033[J");
	data.env = tab_to_list(envp);
	//if (!init_here_doc(&data.here_doc))
	//	return (0);//free l'env
	//modifier pour proteger l'erreur de malloc peut etre null si pas d'env
	while (1)
	{
		printf("ret == %d\n", data.return_value);
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
		if (data.cmd)
				data.return_value = handle_cmds(data.cmd, lst_to_tab(data.env), &data);
		manage_data(&data, 0);
	}
	return (0);
}
