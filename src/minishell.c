/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/07/03 15:24:54 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO faire fonction pour initialiser data

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

	(void)envp;
	if (argc != 1 || argv[1])
	{
		printf("Error:\nThis program don't take arguments\n");
		exit(0);
	}
	while (1)
	{
		data.args = readline(PROMPT);
		if (data.args)
		{
			if (history(data.args) == 0)
			{
				if (check_syntax(data.args) == 0)
				{
					set_cmd(&data);
					while (data.cmd)
					{
						printf("%s\n", data.cmd->cmd);
						data.cmd = data.cmd->next;
					}
				}	
			}
		}
		else
			break ;
	}
	return (0);
}
