/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:54:54 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/30 01:37:20 by madaguen         ###   ########.fr       */
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

typedef struct s_var
{
	int		pip[2];
	t_cmd	*tmp;
	int		i;
	int		is_builtin;
}			t_var;

/*exec*/

void	init_fork(t_fork *fork);
void	init_handle_cmds(t_var *var, t_cmd *cmd);
int		init_pipe(t_var *var);
void	init_exec(t_data *data, t_fork *fork, int *built_in, char *cmd);
char	**join_cmd(char *cmd, char **arg);
void	do_redir(t_cmd *cmd_lst, t_fork *fork, t_data *data);
void	exec(t_cmd *cmd_lst, t_data *data);
void	close_pipe_parent(t_var *var);
int		handle_cmds(t_cmd *cmd, t_data *data);

/* Utils exec */

int		handle_cmds(t_cmd *cmd, t_data *data);
void	close_pipe_child(t_cmd *cmd);
int		open_redir(t_dir *redir, t_fd *fd);
long	ft_atol(char *nbr, int *check);
int		ft_strcmp(const char *s, const char *s1);
char	*ft_join(char *s1, char *s2, char c);
void	ft_error(char *message, char *message2, int info);
void	fail_malloc(void);

/* Heredoc */

# define HERE_DOC_ERROR "minishell: warning: here-document at at line \
0 delimited by "

int		get_infile_heredoc(char *limiter);
int		get_fd(char *file_name, int type);
char	*get_file_name(void);
void	ft_strcpy(char *s1, char *s2);
int		verif_heredoc(char *s1, const char *s2, int n);

/*Utils env*/

char	**lst_to_tab(t_lst *lst);
t_lst	*tab_to_list(char **tab);
t_lst	*ft_new_lst(char *data);
void	ft_add_back(t_lst **lst, t_lst *new);
void	ft_clear_lst(t_lst **lst);
int		lst_size(t_lst *lst);
void	print_list(t_lst *lst);
void	update_shlvl(t_lst **env);
void	update_shlvl_util(t_lst *lst, char *content, t_lst **env);
void	update_path(t_lst **env);
void	update_pwd(t_lst **env);
void	update_env(t_lst **env);
t_lst	*init_env(char **env);

/*Wait*/

int		waiting(t_cmd *cmd, int nb_cmd, t_data *data);
int		get_status(int *status, t_data *data);

/*access*/

char	*get_path(char **env);
int		check_path(char *cmd);
int		is_dir(const char *fileName);
char	*if_dir(char *cmd);
char	*check_access(char *cmd, char **path);
char	*check_all_path(char **pathed, char *cmd, char **path);

/*redir*/

int		dup_pipe(t_cmd *cmd);
int		dup_redir(t_fd fd, t_data *data);
int		open_redir(t_dir *redir, t_fd *fd);
void	close_pipe_child(t_cmd *cmd);
void	close_redir(t_cmd *cmd);
void	open_out(t_fd *fd, t_dir *tmp);
void	open_in(t_fd *fd, t_dir *tmp);
void	open_double(t_fd *fd, t_dir *tmp);

/*quit*/

void	free_and_exit(int res, t_fork fork, t_data *data);
void	free_child(t_fork fork, t_data *data);
void	quit_fail_redir(t_fork fork, t_data *data);

#endif
