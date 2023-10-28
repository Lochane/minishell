/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:54:54 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 01:55:56 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "here_doc.h"
# include "builtin.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>

int		open_redir(t_dir *redir, t_fd *fd);
int		handle_cmds(t_cmd *cmd, t_data *data);
char	**lst_to_tab(t_lst *lst);
t_lst	*tab_to_list(char **tab);
t_lst	*ft_new_lst(char *data);
void	ft_add_back(t_lst **lst, t_lst *new);
void	close_pipe_child(t_cmd *cmd);

/* Utils exec */

long	ft_atol(char *nbr, int *check);
int		ft_strcmp(const char *s, const char *s1);
char	*ft_join(char *s1, char *s2, char c);
void	ft_error(char *message, char *message2, int info);
void	fail_malloc(void);

/* Heredoc */

int		get_infile_heredoc(char *limiter);

#endif
