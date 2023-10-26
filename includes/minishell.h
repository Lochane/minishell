/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:43:14 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/26 20:51:30 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "struct.h"
# include "exec.h"
# include "expansion.h"
# include "here_doc.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
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
# include <errno.h>

/* Code erreur */
# define ERR_SYNTX 2
# define ERR_CMD 127
# define ERR_DIR 126
# define ERR_IDENTIF 1

/* Code signaux */
# define CTRL_C 130
# define CTRL_SLASH 131

extern unsigned char	g_g;

# define PATH "PATH=/usr/local/sbin:/usr/local/bin:\
/usr/sbin:/usr/bin:/sbin:/bin"
# define RED "\x1b[91;1m"
# define RESET "\x1b[0m\2"
# define HEADER "\033[38;5;223;1m"

# define SMILEY "\xf0\x9f\1\x8c\x88\2"
# define PROMPT "\xf0\x9f\1\x8c\x88\2\1\033[38;5;223;1m\2Minihell->\1\x1b[0m\2"

/*builtin*/
# define BUILT_IN_LIST {"echo", "cd", "pwd", "export", "env", "unset", "exit", ((char *)(0))}

/* Set Cmd */
int		tri_cmd(char *tab, t_cmd *cmd);
int		get_arg(char **tab, t_cmd *cmd);
int		get_redirection(char **tab, t_cmd *cmd);
int		set_cmd(t_data	*data);

/* Manage Redirection */
char	*check_space_front(char *tab);
char	*check_space_back(char *tab);
int		manage_redirection(char *token, char *file, t_cmd *cmd);
char	*ft_str_insert_back(char *str, char *insert, int index);
char	*ft_str_insert_front(char *str, char *insert, int index);
char	*manage_space_front(int index, char *tab, int space_count);
char	*manage_space_back(int index, char *tab, int space_count, int j_index);
char	*trim_space(char *tab, char *save_tab);

/* Set Cmd Utils */
t_cmd	*init_cmd(void);
char	*ft_strjoin_shell(char const *s1, char const *s2, int j);
int		tab_size(char **tab);
int		found_space(char *tab, int allow);
int		find_index(int i, char **tab, int allow);

/* Check Syntax*/
int		check_syntax(char *args, t_data *data);
int		check_ampersand(char *args, int i);
int		check_slash(char *args, int i);
int		check_chevron(char *args, int i);
int		check_pipe(char *args, int i);
int		count_chevron(char *args, int i);
char	**split_and_check(t_data *data);

/* Utils */
int		fill_arg(t_cmd *cmd, char **tab);
char	**ft_split_shell(char const *s, char c);
void	initialise_cmd(t_cmd *cmd);
void	add_back(t_cmd *lst, t_cmd *new);
void	*ft_free_tab(char **res, size_t i);
void	add_back_dir(t_dir **lst, t_dir *new);
t_dir	*init_dir(char *file);
void	ft_syntax_error(char *message);
void	manage_data(t_data *data, int allow);
int		remove_lst(t_lst **lst, char *name);
void	ft_clear_lst(t_lst **lst);

/* Signaux */
void	restore_sig(void);
void	ignore_sig(void);
void	sig_handler(int signum);
void	handle_sig(t_data *data);
void	intercept_sig(void);

/* Poubelle */
void	print_tab(char **tab);
void	print_cmds(t_cmd *cmd);

#endif