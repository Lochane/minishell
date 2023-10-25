#include "../includes/minishell.h"

t_lst  *ft_new_lst(char *data)
{
    t_lst   *new;
    int     i;

    new = malloc(sizeof(t_lst));
    if (!new)
        return (NULL);
    i = 0;
    while (data[i] && data[i] != '=')
        i++;
    new->next = NULL;
    new->data = data; 
    new->size = i;
    new->is_env = 1;
    return (new);
}

void    ft_clear_lst(t_lst **lst)
{
    t_lst   *tmp;

    while (*lst)
    {
        tmp = (*lst)->next;
        free((*lst)->data);
        free(*lst);
        *lst = tmp;
    }
}

int lst_size(t_lst *lst)
{
    int i;

    i = 0;
    while (lst)
    {
        lst = lst->next;
        i++;
    }
    return (i);
}

char **lst_to_tab(t_lst *lst)
{
    int     size;
    char    **tab;
    int     i;

    i = 0;
    size = lst_size(lst);
    tab = malloc(sizeof(char *) * (size + 1));
    if (!tab)
        return (NULL);
    while (lst)
    {
        tab[i] = lst->data;
        lst = lst->next;
        i++;
    }
    tab[i] = NULL;
    return (tab);
}

void print_list(t_lst *lst)
{
    while (lst)
    {
        printf("%s\n", lst->data);
        lst = lst->next;
    }
}

void    ft_add_back(t_lst **lst, t_lst *new)
{
    t_lst   *tmp;

    if (!(*lst))
    {
        *lst = new;
        return ;
    }
    tmp = *lst;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}

t_lst  *tab_to_list(char **tab)
{
    int i;
    t_lst  *lst;
    t_lst  *new;

    i = 0;
    lst = NULL;
    if (!tab)
        return (NULL);
    while (tab[i])
    {
        new = ft_new_lst(ft_strdup(tab[i]));
        if (!new)
            return (ft_clear_lst(&lst), lst);
        ft_add_back(&lst, new);
        i++;
    }
    return (lst);
}