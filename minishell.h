/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:43:14 by lsouquie          #+#    #+#             */
/*   Updated: 2023/07/10 16:19:40 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <signal.h>
# include <sys/types.h>
# include "struct.h"

# define PROMPT "minishell>"

/* Set Cmd */
void	tri_cmd(char *tab, t_cmd *cmd);
void	get_arg(char **tab, t_cmd *cmd);
void	set_cmd(t_data	*data);

/* Manage Redirection */
void	check_space_before(char *tab);
void	check_space_after(char *tab);
int		manage_in(char *tab, char *src, t_cmd *cmd, int i);
int		manage_out(char *tab, char *src, t_cmd *cmd, int i);

/* Set Cmd Utils */
t_cmd	*init_cmd(void);
char	*ft_strjoin_shell(char const *s1, char const *s2, int j);
int		tab_size(char **tab);
int		found_space(char *tab, int allow);

/* Check Syntax*/
int		check_syntax(char *args);
int		check_ampersand(char *args, int i);
int		check_slash(char *args, int i);
int		check_chevron(char *args, int i);


/* Utils */
void	print_tab(char **tab);
char	**ft_split_shell(char const *s, char c);
void	initialise_cmd(t_cmd *cmd);
void	add_back(t_cmd *lst, t_cmd *new);
void	*ft_free_tab(char **res, size_t i);


#endif