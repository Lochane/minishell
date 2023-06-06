/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 14:28:49 by lochane           #+#    #+#             */
/*   Updated: 2023/06/06 23:51:55 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lstsize_lexer(t_lexer *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_simple_cmd	*lstnew_simple_cmd(char **content)
{
	t_simple_cmd	*liste;
	int	i;

	i = 0;
	liste = malloc(sizeof(t_simple_cmd));
	if (!liste)
		return (NULL);
	printf("****************************\n");
	print_tab(content);
	while (content[i])
	{
		ft_strlcpy(liste->str[i], content[i], ft_strlen(content[i]));
		i++;
	}
	liste->next = NULL;
	liste->prev = NULL;
	return (liste);
}

void	add_back_simple_cmd(t_simple_cmd **lst, t_simple_cmd *new)
{
	t_simple_cmd	*temp;

	if (!lst || !new)
		return ;
	temp = *lst;
	if (lst && (*lst))
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
		new->prev = temp;
	}
	else
	*lst = new;
}