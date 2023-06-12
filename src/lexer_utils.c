/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:47:25 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/12 16:12:56 by lsouquie         ###   ########.fr       */
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

void	go_prev_lexer(t_lexer **lexer)
{
	while ((*lexer))
		(*lexer) = (*lexer)->prev;
}

void	lexer_remove_two_nodes(t_lexer **lexer)
{
	t_lexer	*node1;
	t_lexer	*node2;

	node1 = *lexer;
	node2 = (*lexer)->next;

	(*lexer) = node2->next;
	if (*lexer != NULL)
		(*lexer)->prev = node1->prev;
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
