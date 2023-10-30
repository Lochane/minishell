/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:44:43 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 01:23:51 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
# include "here_doc.h"
# include "exec.h"

typedef struct s_buffer
{
	char			*buf;
	unsigned long	size;
	unsigned long	index;

}					t_buffer;

typedef struct s_expand
{
	char		nb[11];
	char		*content;
	t_buffer	buffer;
	int			index;
	int			quote[2];
	int			quoted;
}				t_expand;

int		check_char(char c);
void	get_buf(t_buffer *buffer, unsigned long size);
void	stack_itoa(char n[11], unsigned int nb);
void	get_var_content(t_expand *expand, int *tmp, char *str, t_data *data);
void	cpy_var(char *str, t_expand *expand, t_data *data);
char	*do_expand(char **str, t_data *data);
void	expand_arg(char **args, t_data *data);
void	expand_redir(t_dir *redir, t_data *data);
void	expansion(t_data *data);
void	check_quote(char *str, int quote[2], int *index, int *quoted);
void	stack_itoa(char n[11], unsigned int nb);
int		is_quote(char c, int quote[2]);
void	fail_malloc_expand(t_buffer *buffer);
int		allowed_char(char c);
int		check_char(char c);

#endif
