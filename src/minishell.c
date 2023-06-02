/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/02 17:19:54 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data data;
	(void)envp;
	if (argc != 1 || argv[1])
	{
		printf("Error:\nThis progam don't take arguments\n");
		exit(0);
	}
	while (1)
	{
		data.args = readline(PROMPT);
		check_token(&data);
		printf("%s", data.args);
	}
	return (0);
}
