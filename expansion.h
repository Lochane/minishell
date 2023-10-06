#ifndef EXPANSION_H
# define EXPANSION_H

# include "minishell.h"
# include "here_doc.h"
# include "exec.h"

typedef struct s_buf
{
    char	*buf;
    unsigned long	size;
    unsigned long	index;

}       			t_buf;

int		check_char(char c);
void	get_buf(t_buf *buffer);
void	stack_itoa(char n[11], unsigned int nb);
char	*get_var_content(int *tmp, int *index, char *str, t_data data);
void	cpy_var(char *str, int *index, t_buf *buffer, t_data data);
char	*do_expand(char *str, t_data data);
void	expand_arg(char **args, t_data *data);
void	expand_redir(t_dir *redir, t_data *data);
void	expansion(t_data *data);
int		check_quote(char *str, int quote[2], int *index);

#endif