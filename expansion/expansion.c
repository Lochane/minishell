/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 21:16:13 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/10 18:03:19 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expansion.h"

//set param erreur de malloc

void	expand_arg(char **args, t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		str = do_expand(&args[i], *data);
		if (!str)
			return ;
		free(args[i]);
		args[i] = str;
		i++;
	}
}
//set pram erreur de malloc

void	expand_redir(t_dir *redir, t_data *data)
{
	char	*str;

	while (redir)
	{
		str = do_expand(&redir->file, *data);
		if (!str)
			return ;
		free(redir->file);
		redir->file = str;
		redir = redir->next;
	}
}
//set dans data un paramettre pour l'erreur de malloc  verifier dans le main

void	expansion(t_data *data)
{
	t_cmd	*tmp_cmd;
	char	*str;

	tmp_cmd = data->cmd;
	while (tmp_cmd)
	{
		str = do_expand(&tmp_cmd->cmd, *data);
		if (!str)
			return ;
		free(tmp_cmd->cmd);
		tmp_cmd->cmd = str;
		expand_arg(tmp_cmd->arg, data);//check le paamettre erruer de malloc
		expand_redir(tmp_cmd->redirection, data);//check le parametre erreur de malloc
		tmp_cmd = tmp_cmd->next;
	}
}
