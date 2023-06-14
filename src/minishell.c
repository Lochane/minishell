/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/14 17:20:09 by lsouquie         ###   ########.fr       */
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
		data.envp = envp; // pas bien
		check_token(&data);
		check_cmd(&data);
		//print_lexer(data.lexer);
		// printf("%s", data.args);
	}
	return (0);
}

// main(void)
// {
// 	t_lexer	lexer;

// 	while (tab[i])
// 	{
// 		lexer = getlex(lexer, tab[i]);
// 	}
// }

// getlex()
// {
// 	t_lexer lex;
// 	t_lexer tmp;

// 	tmp = lexer;
// 	lex.str = str;
// 	lex.token = t_token token;
// 	lex.next = null;
// 	while (lexer.next)
// 	{
// 		lexer = lexer.next;
// 	}
// 	lex.prev = lexer;
// 	lexer.next = lex;
// 	return (tmp)
// }

// removenode(lexer)
// {
// 	lexer->next->prev = lexer->prev
// 	lexer->prev->next = lexer->next;
// }