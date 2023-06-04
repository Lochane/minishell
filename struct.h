/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:51:16 by lochane           #+#    #+#             */
/*   Updated: 2023/06/04 14:16:52 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

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

typedef struct s_simple_cmd
{
	char **str;	
	int                     num_redirections;
	char                    *hd_file_name;
	t_lexer                 *redirections;
	struct s_simple_cmd *next;
	struct s_simple_cmd *prev;
	
} t_simple_cmd;


typedef struct s_data
{
	char*	args;
	char	**envp;
	t_lexer	*lexer;
	t_simple_cmd *simple_cmd;
}	t_data;

#endif
