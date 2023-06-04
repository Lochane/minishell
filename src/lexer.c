/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lochane <lochane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 15:56:28 by lsouquie          #+#    #+#             */
/*   Updated: 2023/06/04 13:32:53 by lochane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_lexer(t_data *data, t_lexer **lexer)
{
	t_lexer	*tmp_lst;
	char	**tmp;
	int		i;

	i = 0;
	tmp = ft_split(data->args, ' ');
	print_tab(tmp);
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
	int		i;

	data->lexer = NULL;
	set_lexer(data, &data->lexer);
	while (data->lexer)
	{
		i = 0;
		while (data->lexer->str[i])
		{
			if (data->lexer->str[0] == '|' && !data->lexer->str[1])
				data->lexer->token = PIPE;
			else if (data->lexer->str[0] == '<' && !data->lexer->str[1])
				data->lexer->token = LESS;
			else if (data->lexer->str[0] == '<' && data->lexer->str[1] == '<' 
				&& !data->lexer->str[2])
				data->lexer->token = LESS_LESS;
			else if (data->lexer->str[0] == '>' && !data->lexer->str[1])
				data->lexer->token = GREAT;
			else if (data->lexer->str[0] == '>' && data->lexer->str[1] == '>' 
				&& !data->lexer->str[2])
				data->lexer->token = GREAT_GREAT;
			i++;
		}
		data->lexer = data->lexer->next;
	}
}
