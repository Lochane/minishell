/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uaupetit <uaupetit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 10:26:47 by uaupetit          #+#    #+#             */
/*   Updated: 2023/07/06 16:07:49 by uaupetit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h" 

t_env *env_lst(char **envp, t_data *data)
{
	data->env_lst = NULL;
	int j = 0;
	char *line;
	char *equal_sign;
	char *key;
	char *value;
	
	while(envp[j])
	{
		line = envp[j];
		equal_sign = ft_strchr(line, '=');
		if (equal_sign != NULL)
		{
			key = ft_substr(line, 0, equal_sign - line);
			value = ft_strdup(equal_sign + 1);
			if (key && value)
			{
				ft_lstadd_back_two(&(data->env_lst), ft_lstnew_two(key, value));
			}
			else
			{
				free(key);
				free(value);
				free_env_lst(data->env_lst);
				return NULL;
			}
		}
		j++;
	}
	return data->env_lst;
}

void free_env_lst(t_env *env_lst)
{
	t_env *current = env_lst;
	while (current != NULL)
	{
		t_env *next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
}

void ft_lstadd_back_two(t_env **lst, t_env *new)
{
	if (!lst || !new)
		return ;
	new->next = NULL;
	if (*lst)
	{
		t_env *temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*lst = new;
}

t_env	*ft_lstnew_two(char *key, char *value)
{
	t_env *list = (t_env *)malloc(sizeof(t_env));
	if (!list)
		return NULL;
	list->key = key;
	list->value = value;
	list->next = NULL;
	return list;
}

int ft_lstsize_three(t_env *lst)
{
    int size = 0;
    while (lst != NULL)
    {
        size++;
        lst = lst->next;
    }
    return size;
}
/*
void copy_env_to_data(t_data *data)
{
    int i = 0;
    int key_len = 0;
    int value_len = 0;
    int size = ft_lstsize_three(data->env_lst);
    data->envcpy = (char **)malloc((size + 1) * sizeof(char *));
    if (!data->envcpy)
    {
        //free
        return;
    }
    t_env *current = data->env_lst;
    while (current != NULL)
    {
        key_len = ft_strlen(current->key);
        value_len = ft_strlen(current->value);
        data->envcpy[i] = (char *)malloc(key_len + value_len + 2);
        if (!data->envcpy[i])
        {
            //free
            return;
        }
        strncpy(data->envcpy[i], current->key, key_len);
        data->envcpy[i][key_len] = '=';
        strncpy(data->envcpy[i] + key_len + 1, current->value, value_len);
        data->envcpy[i][key_len + value_len + 1] = '\0';
        current = current->next;
        i++;
    }
    data->envcpy[size] = NULL;
}*/

void copy_env_to_data(t_data *data) {
    int i = 0;
    int key_len = 0;
    int value_len = 0;
    int size = ft_lstsize_three(data->env_lst);
    data->envcpy = (char **)malloc((size + 1) * sizeof(char *));
    if (!data->envcpy) {
        // Libérer la mémoire et gérer l'erreur
        return;
    }
    t_env *current = data->env_lst;
    while (current != NULL) {
        key_len = ft_strlen(current->key);
        value_len = ft_strlen(current->value);
        data->envcpy[i] = (char *)malloc(key_len + value_len + 2);
        if (!data->envcpy[i]) {
            // Libérer la mémoire et gérer l'erreur
            return;
        }
        ft_strlcpy(data->envcpy[i], current->key, key_len + 1);
        data->envcpy[i][key_len] = '=';
        ft_strlcpy(data->envcpy[i] + key_len + 1, current->value, value_len + 1);
        current = current->next;
        i++;
    }
    data->envcpy[size] = NULL;
}

