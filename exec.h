#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "here_doc.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

typedef struct s_fd
{
    int in;
    int out;
}       t_fd;

typedef int (*fct)(t_cmd *, t_fd *, t_data *);

int		open_redir(t_dir *redir, t_fd *fd);
int		handle_cmds(t_cmd *cmd, t_data *data);
char	**lst_to_tab(t_lst *lst);
t_lst	*tab_to_list(char **tab);
t_lst	*ft_new_lst(char *data);
void	ft_add_back(t_lst **lst, t_lst *new);

/* Utils exec */

long    ft_atol(char *nbr, int *check);
int	    ft_strcmp(const char *s, const char *s1);
char	*ft_join(char *s1, char *s2, char c);
void	ft_error(char *message, char *message2, int info);


/* Builtin */

int	    is_built_in(char *s);
int	    do_built_in(t_cmd *cmd, t_data *data, int check);
int	    ft_var_cmp(char *s1, int size,char *s2);
int	    do_exit(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_pwd(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_echo(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_cd(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_export(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_unset(t_cmd *cmd, t_fd *fd, t_data *data);
int	    print_env(t_cmd *cmd, t_fd *fd, t_data *data);
char	*ft_get_env(char *var, int size, t_lst *env, t_lst **lst);

/* Heredoc */

int		get_infile_heredoc(char *limiter);

/* utils builtin */
char	*ft_strjoin_pool(int size, char **strs, char *sep, int new_line);


#endif