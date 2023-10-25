#ifndef BUILTIN_H
# define BUILTIN_H

# define ECHO_OPTIONS "n"
# define EXPORT_OPTION ""
# define UNNSET_OPTION ""
# define CD_OPTION ""
# define PWD_OPTION ""
# define ENV_OPTION ""

typedef int (*fct)(t_cmd *, t_fd *, t_data *);

/* Builtin */

int	    is_built_in(char *s);
int	    do_built_in(t_cmd *cmd, t_data *data, int check);
int	    ft_var_cmp(char *s1, int size,char *s2);
int	    do_exit(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_pwd(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_echo(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_cd(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_export(t_cmd *cmd, t_fd *fd, t_data *data);
int	    do_unset(t_cmd *cmd, t_fd *fd, t_data *data);
int	    print_env(t_cmd *cmd, t_fd *fd, t_data *data);
char	*ft_get_env(char *var, int size, t_lst *env, t_lst **lst);

/* utils builtin */
char	*ft_strjoin_pool(int size, char **strs, char *sep, int new_line);
int     check_options(char **args, char *options, char *found, char *invalid);
void	error_option(char *cmd, char invalid);
int     find_char(char c, char *str);

#endif