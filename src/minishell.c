/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/20 12:20:56 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO faire fonction pour initialiser data

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
			if (check_syntax(data.args) == 0)
				set_cmd(&data);
		}
		else
			break ;
	}
	return (0);
}