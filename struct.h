/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:51:16 by lochane           #+#    #+#             */
/*   Updated: 2023/06/16 14:38:18 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cmd
{
	char	*cmd; // ls
	char 	**arg; // [0] -l [1] -a [2] sources
	char	*in; // < coucou < salut < bonjour << cc
	char	*out; // >> heredoc > out > out2
	struct	s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	*args;
	t_cmd	cmd;
}	t_data;

#endif
