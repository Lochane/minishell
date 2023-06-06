/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:43:14 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/06 22:48:06 by lochane          ###   ########.fr       */
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
void	ft_add_back_lexer(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lstnew_lexer(void *content);

/* Lexer */
int	set_lexer(t_data **data, t_lexer **lexer);
int	check_token(t_data *data);

/* Parsing */
void	copy_cmd(t_simple_cmd **simple_cmd, t_lexer *lexer);
void 	check_cmd(t_data *data);

/* Parsing Utils */
int	lstsize_lexer(t_lexer *lst);
t_simple_cmd	*lstnew_simple_cmd(char **content);
void	add_back_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new);

/* Utils */
void	print_lexer(t_lexer *data);
void	print_simple_cmd(t_simple_cmd *data);
void	print_tab(char **tab);

#endif