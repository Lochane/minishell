/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 15:48:35 by uaupetit          #+#    #+#             */
/*   Updated: 2023/07/06 18:14:29 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_built_in(t_data *data)
{
    int i = 0;
    char *tab[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
    while (tab[i])
    {
        if (ft_strncmp(data->cmd->cmd, tab[i], ft_strlen(data->cmd->cmd)) == 0)
            return (1);
        i++;
    }
    return (0);
}

int ft_lstsize_two(t_cmd *lst)
{
    int size = 0;
    t_cmd *current = lst;
    while (current != NULL)
    {
        size++;
        current = current->next;
    }
    //printf("size = %d\n")
    return size;
}

void execute_cmd(t_data *data)
{
    if (ft_lstsize_two(data->cmd) == 1)
    {
        printf("size = 1\n");
        if (is_built_in(data) == 0)
            execute_sc(data);
      /*else
            executer commande built in*/
    } 
    else if (ft_lstsize_two(data->cmd) == 2)
    {
        printf("size = 2\n");
        //pipex(data);
        //penser a rechecker si il y a des built in dans le programme
    }
    //else
       // multipipe
}

char **merge_tab(t_data *data)
{
    char **cmd;
    int size = tab_size_two(data->cmd->arg) + 1;
    int i = 0;
    int j = 0;
    cmd = malloc(sizeof(char *) * (size + 1));
    // security
    if (cmd == NULL)
    {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    cmd[i] = ft_strdup(data->cmd->cmd);
    // security
    if (cmd[i] == NULL)
    {
        perror("Erreur lors de l'allocation de mémoire");
        exit(EXIT_FAILURE);
    }
    i++;
    j = 0;
    while (data->cmd->arg[j] != NULL)
    {
        cmd[i] = ft_strdup(data->cmd->arg[j]);
        // security
        if (cmd[i] == NULL)
        {
            perror("Erreur lors de l'allocation de mémoire");
            exit(EXIT_FAILURE);
        }
        i++;
        j++;
    }
    cmd[i] = NULL;
    return cmd;
}

void execute_sc(t_data *data)
{
    char *path;
    char **cmd;
    int i = 0;
    path = find_path(data);
    if (tab_size_two(data->cmd->arg) > 0)
        cmd = merge_tab(data);
    if (!path)
    {
        write(2, "command not found\n", 18);
        // free_split(cmd);
        return;
    }
    if (tab_size_two(data->cmd->arg) > 0)
    {
        if (execve(path, cmd, data->path) == -1)
        {
            perror("Permission denied");
            //   free(path);
            // free_split(cmd);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (execve(path, &data->cmd->cmd, data->path) == -1)
        {
            perror("Permission denied");
            //   free(path);
            // free_split(cmd);
            exit(EXIT_FAILURE);
        }
    }
}

char *find_path(t_data *data)
{
    char *path;
    if (access(data->cmd->cmd, F_OK) == 0)
        return (data->cmd->cmd);
    // if (lst_env->line == NULL)
    //	return (NULL);
    path = search_paths(data, path);
    printf("path = %s\n", path);
    // free_split(paths);
    return (path);
}

int tab_size_two(char **tab)
{
    int i = 0;
    if (!tab)
        return 0;
    while (tab[i])
        i++;
    return (i);
}

char *search_paths(t_data *data, char *path)
{
    int i;
    char *part_path;
    i = 0;
    while (data->path[i])
    {
        part_path = ft_strjoin(data->path[i], "/");
        path = ft_strjoin(part_path, data->cmd->cmd);
        if (access(path, F_OK) == 0)
        {
            free(part_path);
            return (path);
        }
        free(part_path);
        free(path);
        i++;
    }
    return (NULL);
}