#ifndef EXEC_H
# define EXEC_H

# include "here_doc.h"
# include <sys/types.h>
# include <sys/wait.h>

int handle_cmds(t_cmd *cmd, char **env);


#endif