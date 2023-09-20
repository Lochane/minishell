#include "../minishell.h"

char **lst_to_tab(t_list *list)
{
    int     size;
    char    **tab
    int     i;

    i = 0;
    size = lst_size(list);
    if (size == 0)
        return (NULL);
    tab = malloc(sizeof(char *) * (size + 1))
    if (!tab)
        return (NULL);
    while (lst)
    {
        tab[i] = list->content;
        lst = lst->next;
        i++;
    }
    tab[i] = NULL;
    return (tab)
}

t_list  *tab_to_list(char **tab)
{
    int i;
    t_list  *lst;
    t_list  *new;

    i = 0;
    lst = NULL;
    if (!tab)
        return (NULL);
    while (tab[i])
    {
        new = ft_lstnew(tab[i]);
        if (!new)
            ft_lstclear(lst);
        ft_lstadd_back(&lst, new);
    }
    return (lst);
}