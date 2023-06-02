/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:43:14 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/02 17:27:00 by lsouquie         ###   ########.fr       */
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

# define PROMPT "minishell>"

typedef struct s_data
{
	char*	args;
}	t_data;

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
}	t_tokens;

typedef struct s_lexer
{
	char *str;
	t_tokens token;
	struct s_lexer *next;
	struct s_lexer *prev;
} t_lexer;


void	ft_add_back_lexer(t_lexer **lst, t_lexer *new);
t_lexer	*ft_lstnew_lexer(void *content);
void	print_lst(t_lexer *data);

void	set_lexer(t_data *data, t_lexer **lexer);
void	check_token(t_data *data);


#endif