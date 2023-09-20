#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "here_doc.h"
# include <sys/types.h>
# include <sys/wait.h>

int handle_cmds(t_cmd *cmd, char **env);
//char **lst_to_tab(t_list *list);
//t_list  *tab_to_list(char **tab);

#endif