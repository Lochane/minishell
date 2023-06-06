/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/06 23:28:01 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO faire fonction pour initialiser data

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	
	// print_tab(envp);
	if (argc != 1 || argv[1])
	{
		printf("Error:\nThis progam don't take arguments\n");
		exit(0);
	}
	while (1)
	{
		data.args = readline(PROMPT);
		data.envp = envp;
		check_token(&data);
		check_cmd(&data);
		//print_lexer(data.lexer);
		// printf("%s", data.args);
	}
	return (0);
}
