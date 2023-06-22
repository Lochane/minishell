/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:51:16 by lochane           #+#    #+#             */
/*   Updated: 2023/06/20 17:25:08 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	char			*in;
	char			*out;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	*args;
	t_cmd	*cmd;
}	t_data;

#endif
