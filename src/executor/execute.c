/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:17:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/08 16:48:05 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	close_fds_at_error(int cmd, t_data *data);

void	execute(int cmd, char **cmd_args, t_data *data)
{
	int		exec;

	exec = execve(data->exec->cmds[cmd]->name, cmd_args, data->virtual_envp);
	if (exec == -1)
	{
		close_fds_at_error(cmd, data);
		data->error_msg = ft_strjoin(ft_strdup(data->exec->cmds[cmd]->name),
				": command not found\n");
		exit_error(127, data->error_msg, data);
	}
}

static void	close_fds_at_error(int cmd, t_data *data)
{
	// if (cmd == data->n_cmds - 1 && data->files.outfile_fd != -1)
	// 	close(data->files.outfile_fd);
	// if (data->files.infile_fd != -1)
	// 	close(data->files.infile_fd);
	// if (cmd > 0)
	// 	close(data->files.pipes[cmd - 1][0]);
	// close(data->files.pipes[cmd][1]);
	// close(data->files.pipes[cmd][0]);
	// close(1);
	// close(0);
}
