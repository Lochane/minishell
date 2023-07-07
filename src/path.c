/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 17:18:18 by uaupetit          #+#    #+#             */
/*   Updated: 2023/07/04 17:55:23 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void path_init(t_data *data)
{
    t_env *current = data->env_lst;
    char *path_value = NULL;
    while (current)
    {
        if (ft_strncmp(current->key, "PATH", 4) == 0)
        {
            path_value = current->value;
            break;
        }
        current = current->next;
    }
    if (path_value == NULL)
    {
        return;
    }

    data->path = ft_split(path_value, ':');
    if (data->path == NULL)
    {
        return;
    }
}

