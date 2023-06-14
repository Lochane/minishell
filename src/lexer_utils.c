/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:47:25 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/14 13:57:07 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*ft_lstnew_lexer(void *content)
{
	t_lexer	*liste;

	liste = malloc(sizeof(t_lexer));
	if (!liste)
		return (NULL);
	liste->str = content;
	liste->next = NULL;
	liste->prev = NULL;
	return (liste);
}

void	ft_add_back_lexer(t_lexer **lst, t_lexer *new)
{
	t_lexer	*temp;

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

void	go_prev_lexer(t_lexer **lexer, int allow)
{
	while ((*lexer)->prev)
	{
		if ((*lexer)->prev->token == 1 && allow == 1)
			break ;
		(*lexer) = (*lexer)->prev;
	}
}

void	lexer_remove_two_nodes(t_lexer **lexer)
{
	t_lexer	*node1;
	t_lexer	*node2;

	node1 = *lexer;
	node2 = (*lexer)->next;
	if (node1->prev != NULL)
		node1->prev->next = node2;
	if (node2->next != NULL)
		node2->next->prev = node1;
	if (*lexer == node1)
		*lexer = node2->next;
	free(node1);
	free(node2);
}

int	lstsize_lexer(t_lexer *lst)
{
	int	size;

	size = 0;
	while (lst != NULL)
	{
		if (lst->token == 1)
			break ;
		size++;
		lst = lst->next;
	}
	return (size);
}

void	lexer_remove_nodes(t_lexer **lexer)
{
	t_lexer	*node;

	node = *lexer;
	if (node->prev != NULL)
		node->prev->next = node->next;
	if (node->next != NULL)
		node->next->prev = node->prev;
	*lexer = node->next;
	free(node);
}