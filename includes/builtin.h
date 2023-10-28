/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 01:48:19 by madaguen          #+#    #+#             */
/*   Updated: 2023/10/29 01:54:19 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define ECHO_OPTIONS "n"
# define EXPORT_OPTION ""
# define UNNSET_OPTION ""
# define CD_OPTION ""
# define PWD_OPTION ""
# define ENV_OPTION ""
# define EXPORT_USAGE "export: usage: export [no option] [name[=value] ...]\n"
# define UNSET_USAGE "unset: usage: unset [no option] [name ...]\n"
# define CD_USAGE "cd: usage: cd [-n] [dir]\n"
# define PWD_USAGE "pwd: usage: pwd [no option]\n"
# define ENV_USAGE "env: usage: env [no option]\n"

typedef int	(*t_fct)(t_cmd *, t_fd *, t_data *);

typedef struct s_cd
{
	t_lst	*pwd;
	t_lst	*oldpwd;
	char	*oldpwdpath;
	char	*pwdpath;
	char	option[0];
	int		check;
	char	invalid;
	char	*arg;
}			t_cd;

typedef struct s_exit
{
	int		check;
	long	nb;
	int		i;
	int		tty;
}	t_exit;

typedef struct s_export
{
	t_lst	*var;
	int		i;
	int		check;
	char	*message;
	int		is_env;
	char	*content;
	char	option[0];
	char	invalid;
}			t_export;

typedef struct s_env
{
	int		final_fd;
	char	*str;
	int		check;
	char	opt[0];
	char	inv;
}			t_env;

typedef struct s_pwd
{
	char	*var;
	int		final_fd;
	char	*str;
	char	invalid;
	int		check;
	char	opt[0];
}			t_pwd;

/* Builtin */

int		is_built_in(char *s);
int		do_built_in(t_cmd *cmd, t_data *data, int check, int index);
int		ft_var_cmp(char *s1, int size, char *s2);
int		do_exit(t_cmd *cmd, t_fd *fd, t_data *data);
int		do_pwd(t_cmd *cmd, t_fd *fd, t_data *data);
int		do_echo(t_cmd *cmd, t_fd *fd, t_data *data);
int		do_cd(t_cmd *cmd, t_fd *fd, t_data *data);
int		do_export(t_cmd *cmd, t_fd *fd, t_data *data);
int		do_unset(t_cmd *cmd, t_fd *fd, t_data *data);
int		print_env(t_cmd *cmd, t_fd *fd, t_data *data);
char	*ft_get_env(char *var, int size, t_lst *env, t_lst **lst);

/* utils builtin */
int		ft_var_cmp(char *s1, int size, char *s2);
char	*ft_get_env(char *var, int size, t_lst *env, t_lst **lst);
char	*ft_strjoin_pool(int size, char **strs, char *sep, int new_line);
int		check_options(char **args, char *options, char *found, char *invalid);
void	error_option(char *cmd, char invalid);
int		find_char(char c, char *str);
int		verif_option(t_export *export, t_cmd *cmd);
void	init_export(t_export *export);
int		check_var(char *str);

#endif
