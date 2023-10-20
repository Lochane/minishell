/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:16:13 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/20 21:08:53 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

void	expand_arg(char **args, t_data *data)
{
	int		i;
	int		j;
	int		tmp;
	char	*str;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		str = do_expand(&args[i], data);
		if (!str)
		{
			j = i + 1;
			tmp = i;
			while (args[j])
				args[tmp++] = args[j++];
			args[tmp] = NULL;			
		}
		else
		{
			free(args[i]);
			args[i] = str;
			i++;
		}
	}
}

void	expand_redir(t_dir *redir, t_data *data)
{
	char	*str;

	while (redir)
	{
		if (data->return_value == 12)
			return ;
		str = do_expand(&redir->file, data);
		free(redir->file);
		redir->file = str;
		redir = redir->next;
	}
}

void	expansion(t_data *data)
{
	t_cmd	*tmp_cmd;
	char	*str;

	tmp_cmd = data->cmd;
	while (tmp_cmd)
	{
		if (data->return_value == 12)//a mettre a jour partout
			return ;
		str = do_expand(&tmp_cmd->cmd, data);
		free(tmp_cmd->cmd);
		tmp_cmd->cmd = str;
		expand_arg(tmp_cmd->arg, data);//check le paamettre erruer de malloc
		expand_redir(tmp_cmd->redirection, data);//check le parametre erreur de malloc
		tmp_cmd = tmp_cmd->next;
	}
}
