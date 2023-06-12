/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:43:14 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/12 16:41:54 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "struct.h"

# define PROMPT "minishell>"

/*	Lexer Utils */
/* Fonction utilisee pour gerer le liste chainee de type t_lexer*/
void	go_prev_lexer(t_lexer **lexer);
void	ft_add_back_lexer(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lstnew_lexer(void *content);
void	lexer_remove_two_nodes(t_lexer **lexer);
int		lstsize_lexer(t_lexer *lst);

/* Simple Cmd Utils */
/* Fonction utilisee pour gerer le liste chainee de type t_simple_cmd*/
t_simple_cmd	*lstnew_simple_cmd(char **content, int size);
void	add_back_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new);

/* Lexer */
int		set_lexer(t_data **data, t_lexer **lexer);
int		check_token(t_data *data);

/* Parsing */
void	copy_cmd(t_simple_cmd **simple_cmd, t_lexer *lexer);
void	check_cmd(t_data *data);
void	check_redirection(t_lexer **redirection, t_lexer *lexer);



/* Utils */
void	print_lexer(t_lexer *data);
void	print_simple_cmd(t_simple_cmd *data);
void	print_tab(char **tab);

#endif