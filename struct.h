/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 13:51:16 by lochane           #+#    #+#             */
/*   Updated: 2023/09/05 15:01:47 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft/libft.h"

typedef enum s_tokens
{
	GREAT = 1,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	DOUBLE,
}	t_tokens;

typedef struct s_dir
{
	char			*file;
	t_tokens		token;
	struct s_dir	*next;
}	t_dir;

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	t_dir			*redirection;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	char	*args;
	t_cmd	*cmd;
}	t_data;

#endif
