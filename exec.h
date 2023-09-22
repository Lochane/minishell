#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "here_doc.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_fd
{
    int in;
    int out;
}       t_fd;

typedef int (*fct)(t_cmd *, char **, t_fd);

int handle_cmds(t_cmd *cmd, char **env);
char **lst_to_tab(t_lst *lst);
t_lst  *tab_to_list(char **tab);

#endif