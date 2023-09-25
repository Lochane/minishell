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

typedef int (*fct)(t_cmd *, char **, t_fd, t_data);

int handle_cmds(t_cmd *cmd, char **env, t_data data);
char **lst_to_tab(t_lst *lst);
t_lst  *tab_to_list(char **tab);

#endif