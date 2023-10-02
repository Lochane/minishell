
#include "../minishell.h"
//#include <stdio.h>

int	check_char(char c)
{
	unsigned int	i;
	const char		*protected = "$:=\"'` ";

	printf("%s\n", protected);
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

int	cpy_var(char *res, int size, char *var)
{

}

char	*do_expand(char *str, t_lst *env, t_data data)
{
	int		i;
	int		quote[2];// 0 == " 1 == '
	int		size;
	int		res_i;
	char	*res;

	i = 0;
	res_i = 0;
	quote[0] = 0;
	quote[1] = 0;
	res = NULL;
	size = 0;
	while (str[i])
	{
		//allocrealloc
		if (str[i] == '"' && !quote[1])
			quote[0] = (quote[0] != 1);
		if (str[i] == 47 && !quote[0])
			quote[1] = (quote[1] != 1);
		if (quote[1])
			res[res_i++] = str[i++];//nem pas recopier si quote voir si possible de copier qu'une fois
		else
		{
			if (str[i] == '$')
				res_i += cpy_var(&res[res_i], size - res_i, get_var(&str[i + 1], &i, env));//get var strstr sur l'env check si pas trouve inscrementer i jusuq'a un token spe sinon incrementer i de taille de var si str == $ et +1 == spe copier $ et char spe ca va pas revoir dmain
			else
				res[res_i++] = str[i++];//ne pas recopier si quote
		}
	}
}

void	expand_arg(char **args, t_lst *env, t_data data)
{
	int		i;
	char	*str;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		str = do_expand(args[i], env, data);
		free(args[i]);
		args[i] = str;
		i++;
	}
}

void	expand_redir(t_dir *redir, t_lst *env, t_data data)
{
	while (redir)
	{
		do_expand(redir->file, data.env, data);
		redir = redir->next;
	}
}

void    expansion(t_data *data)
{
    t_cmd	*tmp_cmd;
	int		i;

	tmp_cmd = data->cmd;
	while (tmp_cmd)
	{
		do_expand(tmp_cmd->cmd, data->env, *data);
		expand_arg(tmp_cmd->arg, data->env, *data);
		expand_redir(tmp_cmd->redirection, data->env, *data);
		tmp_cmd = tmp_cmd->next;
	}
}