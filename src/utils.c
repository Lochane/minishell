/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:53:21 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/02 17:29:30 by lsouquie         ###   ########.fr       */
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
	}
	else
	*lst = new;
}

void	print_lst(t_lexer *data)
{
	while (data)
	{
		ft_printf("%d", data->token);
		data = data->next;
	}
	ft_printf("\n");
}
