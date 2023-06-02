/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:56:28 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/02 17:37:34 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_lexer(t_data *data, t_lexer **lexer)
{
	t_lexer	*tmp_lst;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(data->args, 20);
	while (tmp[i])
	{
		tmp_lst = ft_lstnew_lexer(tmp[i]);
		ft_add_back_lexer(lexer, tmp_lst);
		tmp_lst = tmp_lst->next;
		i++;
	}
}

void	check_token(t_data *data)
{
	t_lexer	*lexer;
	int		i;

	set_lexer(data, &lexer);
	while (lexer)
	{
		i = 0;
		while (lexer->str[i])
		{
			if (lexer->str[0] == '|' && !lexer->str[1])
				lexer->token = PIPE;
			else if (lexer->str[0] == '<' && !lexer->str[1])
				lexer->token = LESS;
			else if (lexer->str[0] == '<' && lexer->str[1] == '<' \
				&& !lexer->str[2])
				lexer->token = LESS_LESS;
			else if (lexer->str[0] == '>' && !lexer->str[1])
				lexer->token = GREAT;
			else if (lexer->str[0] == '>' && lexer->str[1] == '>' \
				&& !lexer->str[2])
				lexer->token = GREAT_GREAT;
			i++;
		}
		lexer = lexer->next;
	}
}
