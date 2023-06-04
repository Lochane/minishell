/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:47:25 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/04 14:39:03 by lochane          ###   ########.fr       */
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