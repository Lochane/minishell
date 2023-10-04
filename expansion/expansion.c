
#include "../exec.h"
//#include <stdio.h>

int	check_char(char c)
{
	unsigned int	i;
	const char		*protected = "$:=\"'` ";

	if (c == 0)
		return (0);
	i = 0;
	while (protected[i])
	{
		if (c == protected[i])
			return (0);
		i++;
	}
	return (1);
}

void	get_buf(char **buf, unsigned long *size)
{
	char			*tmp;
	unsigned long	i;

	if (!*buf)
	{
		*buf = malloc(sizeof(char) * 151);
		if (!*buf)
			return ;
		*size = 150;
		return ;
	}
	tmp = malloc((*size * 2) + 1);
	if (!tmp)
	{
		free (*buf);
		*size = 0;
		return ;
	}
	i = -1;
	while (++i < *size)
		tmp[i] = *buf[i];
	free(*buf);
	*buf = tmp;
	*size *= 2;
}

char	*ft_strndup(char *str, int size)
{
	char	*new;
	int		i;

	new = malloc(size + 1);
	if (new)
	{
		i = 0;
		while (i < size)
		{
			new[i] = str[i];
			i++;
		}
		new[i] = 0;
	}
	return (new);
}

void	cpy_var(char *str, int *i, char **res, unsigned long *res_i, unsigned long *size, t_lst *env)
{
	int		tmp;
	char	*content;
	char	*var;
	t_lst	*lst;

	tmp = 0;
	while (str[*i + 1 + tmp] && check_char(str[*i + 1 + tmp]))
		tmp++;
	var = ft_strndup(&str[*i + 1], tmp);//proteger malloc
	(*i) += tmp + 1;
	content = ft_get_env(var, env, &lst);
	if (lst)
	{
		if (*res_i + ft_strlen(content) == *size)
			get_buf(res, size);//proteger le null
		while (*content)
		{
			(*res)[(*res_i)++] = *content;
			content++;
		}
		(*res)[*res_i] = 0;
	}
}

char	*do_expand(char *str, t_data data)
{
	int		i;
	int		quote[2];// 0 == " 1 == ' mettre defin SIMPLE DOUBLE?
	int		quoted;
	unsigned long	size;
	unsigned long	res_i;
	char	*res;

	i = 0;
	res_i = 0;
	quote[0] = 0;
	quote[1] = 0;
	quoted = 0;
	res = NULL;
	size = 0;
	while (str[i])
	{
		if (res_i == size)
			get_buf(&res, &size);
		if (!res)
			return(NULL);//set erreur malloc
		if ((str[i] == '"' && !quote[1]) || (str[i] == 39 && !quote[0]))
		{
			if (str[i] == '"')
				quote[0] = (quote[0] != 1);
			else
				quote[1] = (quote[1] != 1);
			quoted++;
			i++;
		}
		else
		{
			if (str[i] != '$' || quote[1])
				res[res_i++] = str[i++];
			else
				cpy_var(str, &i, &res, &res_i, &size, data.env);
		}
	}
	res[res_i] = 0;
	if (!res_i && !quoted)
	{
		free(res);
		res = NULL;
	}
	return (res);
}

void	expand_arg(char **args, t_data data)
{
	int		i;
	char	*str;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		str = do_expand(args[i], data);//proteger alloc
		free(args[i]);
		args[i] = str;
		i++;
	}
}

void	expand_redir(t_dir *redir, t_data data)
{
	char	*str;

	while (redir)
	{
		str = do_expand(redir->file, data);//proteger alloc
		free(redir->file);
		redir->file = str;
		redir = redir->next;
	}
}

void    expansion(t_data *data)
{
    t_cmd	*tmp_cmd;
	//int		i;
	char	*str;

	tmp_cmd = data->cmd;
	while (tmp_cmd)
	{
		str = do_expand(tmp_cmd->cmd, *data);//proteger alloc
		free(tmp_cmd->cmd);
		tmp_cmd->cmd = str;
		expand_arg(tmp_cmd->arg, *data);//proteger alloc
		expand_redir(tmp_cmd->redirection, *data);//proteger alloc
		tmp_cmd = tmp_cmd->next;
	}
}