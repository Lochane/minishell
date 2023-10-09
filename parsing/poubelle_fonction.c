
#include "../includes/minishell.h"


void    print_cmds(t_cmd *cmd)
{
    while (cmd)
    {
        printf("****maillon*****\ncmd = %s\n", cmd->cmd);
        if (cmd->arg)
        {
            for (int i = 0; cmd->arg[i]; i++)
                printf("arg == %s\n", cmd->arg[i]);
        }
        if (cmd->redirection)
        {
            for (t_dir *tmp = cmd->redirection; tmp; tmp = tmp->next)
                printf("redirection = %s\ntoken = %d\n", tmp->file, tmp->token);
        }
        printf("**********\n");
        cmd = cmd->next;
    }
}

// void	print_tab(char **tab)
// {
// 	int i = 0;

// 	while (tab[i] != NULL)
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// }