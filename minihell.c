/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/12 19:22:33 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

unsigned char	g_g;

void	manage_data(t_data *data, int allow)
{
	t_cmd	*tmp;
	t_dir	*tmp_dir;

	if (allow == 0)
	{
		data->args = NULL;
		data->cmd = NULL;
	}
	else
	{
		while (data->cmd)
		{
			while (data->cmd->redirection)
			{
				free(data->cmd->redirection->file);
				tmp_dir = data->cmd->redirection->next;
				if (data->cmd->redirection->fd != -1)
					close(data->cmd->redirection->fd);
				free(data->cmd->redirection);
				data->cmd->redirection = tmp_dir;
			}
			ft_free_tab(data->cmd->arg, tab_size(data->cmd->arg));
			free(data->cmd->cmd);
			tmp = data->cmd->next;
			free(data->cmd);
			data->cmd = tmp;
		}
		free(data->args);
		data->args = NULL;
		data->cmd = NULL;
	}
}





int	history(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			add_history(str);
			return (0);
		}
		i++;
	}
	return (1);
}


char	*get_line(t_data data)
{
	char	*line;
	int		len;

	if (data.tty == 0)
	{
		line = get_next_line(0);
		if (!line)
			return (NULL);
		len = ft_strlen(line);
		len -= (line[len - 1] == '\n');
		line[len] = 0;
		return (line);
	}	
	else
		return (readline(PROMPT));
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argv;
	if (argc != 1)
	{
		write(2, "Error:\nThis program don't take arguments\n", 42);
		exit(0);
	}
	data.tty = isatty(0);
	if (data.tty)
		printf("\033[H\033[J");
	g_g = 0;
	data.new_line = 0;
	data.return_value = 0;
	data.fd = dup(0);
	if (data.fd == -1)
		return (perror("dup"), errno);
	data.env = tab_to_list(envp);
	if (envp[0] && !data.env)
		return (ft_putstr_fd("echec d'allocation\n", 2), errno);
	while (1)
	{
		intercept_sig();
		manage_data(&data, 0);
		data.args = get_line(data);
		if (g_g == 130)
			handle_sig(&data);
		else
		{	
			if (data.args)
			{
				if (history(data.args) == 0)
				{
					if (check_syntax(data.args, &data) == 0)
					{
						if (!set_cmd(&data))
						{
							if (g_g == 130)
							{
								if (data.new_line)
									write(1, "\n", 1);
								handle_sig(&data);
							}
							manage_data(&data, 1);
						}
					}
				}
			}
			else
			{
				manage_data(&data, 1);
				do_exit(data.cmd, NULL, &data);
				break ;
			}
			expansion(&data);
			if (data.cmd)
					data.return_value = handle_cmds(data.cmd, &data);
			manage_data(&data, 1);
		}
	}
	return (0);
}
