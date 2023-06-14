/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:48:42 by lochane           #+#    #+#             */
/*   Updated: 2023/06/14 14:33:07 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// TODO protéger malloc



void	check_redirection(t_lexer **redirection, t_lexer **lexer)
{
	t_lexer	*tmp;

	go_prev_lexer(lexer, 1);
	redirection = malloc(sizeof(t_lexer));
	while ((*lexer))
	{
		if ((*lexer)->token > 1)
		{
			tmp = ft_lstnew_lexer((*lexer)->str);
			tmp->token = (*lexer)->token;
			ft_add_back_lexer(redirection, tmp);
			tmp = ft_lstnew_lexer((*lexer)->next->str);
			ft_add_back_lexer(redirection, tmp);
			if ((*lexer)->next->next)
				lexer_remove_two_nodes(lexer);
			else
			{
				(*lexer) = (*lexer)->prev;
				(*lexer)->next = NULL;
				break ;
			}
		}
		else
		{
			if (!(*lexer)->next)
				break ;
			else
			(*lexer) = (*lexer)->next;
		}
	}
	go_prev_lexer(lexer, 0);
}

void	copy_cmd(t_simple_cmd **simple_cmd, t_lexer *lexer)
{
	t_simple_cmd	*tmp;
	int				i;
	char			**tab;
	int				size;

	go_prev_lexer(&lexer, 1);
	i = 0;
	size = lstsize_lexer(lexer);
	tab = malloc(sizeof(char **) * (size + 1));
	while (lexer)
	{
		if (lexer->token == 1)
		{
			lexer_remove_nodes(&lexer);
			break ;
		}
		tab[i] = lexer->str;
		lexer_remove_nodes(&lexer);
		i++;
	}
	tab[i] = NULL;
	tmp = lstnew_simple_cmd(tab, size);
	add_back_simple_cmd(simple_cmd, tmp);
	free(tab);
}

void	check_cmd(t_data *data)
{
	data->simple_cmd = NULL;
	if (data->lexer)
		go_prev_lexer(&data->lexer, 0);
	while (data->lexer)
	{
		if (data->lexer->token == 1)
		{
			check_redirection(&data->simple_cmd->redirections, &data->lexer);
			copy_cmd(&data->simple_cmd, data->lexer);
		}
		else if (data->lexer->next == NULL)
		{
			check_redirection(&data->simple_cmd->redirections, &data->lexer);
			copy_cmd(&data->simple_cmd, data->lexer);
		}
		data->lexer = data->lexer->next;
	}
	if (data->simple_cmd)
		go_prev_simple_cmd(&data->simple_cmd);
	print_simple_cmd(data->simple_cmd);
}
