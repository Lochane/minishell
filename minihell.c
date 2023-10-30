/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsouquie <lsouquie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 13:42:59 by lsouquie          #+#    #+#             */
/*   Updated: 2023/10/30 20:29:56 by lsouquie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

unsigned char	g_g;

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

static void	init(t_data *data, char **envp, int argc, char **argv)
{
	(void) argv;
	if (argc != 1)
	{
		write(2, "Error:\nThis program don't take arguments\n", 42);
		exit(0);
	}
	data->tty = isatty(0);
	if (data->tty)
		printf("\033[H\033[J\n");
	g_g = 0;
	data->new_line = 0;
	data->return_value = 0;
	data->fd = dup(0);
	if (data->fd == -1)
		return (perror("dup"), exit(errno));
	data->env = init_env(envp);
}

void	parsing(t_data *data)
{
	if (data->args)
	{
		if (history(data->args) == 0)
		{
			if (check_syntax(data->args, data) == 0)
			{
				if (!set_cmd(data))
				{
					if (g_g == 130)
					{
						if (data->new_line)
							write(1, "\n", 1);
						handle_sig(data);
					}
					manage_data(data, 1);
				}
			}
		}
	}
	else
	{
		manage_data(data, 1);
		do_exit(data->cmd, NULL, data);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	init(&data, envp, argc, argv);
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
			parsing(&data);
			if (data.cmd)
				expansion(&data);
			if (data.cmd && data.return_value != 12)
				data.return_value = handle_cmds(data.cmd, &data);
			manage_data(&data, 1);
		}
	}
	return (0);
}
