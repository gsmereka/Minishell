/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:27:29 by gsmereka          #+#    #+#             */
/*   Updated: 2022/12/29 14:05:58 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static void	exit_error(int cmd, char *file, t_data *data);
static void	close_fds_at_error(int cmd, t_data *data);

void	redirect_input(int cmd, t_data *data)
{
	int	dup_work;

	dup_work = 0;
	if (cmd == 0)
	{
		if (data->files.infile_fd == -1)
			exit_error(cmd, data->files.infile, data);
		dup_work = dup2(data->files.infile_fd, STDIN_FILENO);
	}
	if (cmd > 0)
		dup_work = dup2(data->files.pipes[cmd - 1][0], STDIN_FILENO);
	if (dup_work == -1)
		finalize("Failed to execute dup2(2)", 24, data);
}

void	redirect_output(int cmd, t_data *data)
{
	int	dup_work;

	dup_work = 0;
	if (cmd != data->n_cmds - 1)
		dup_work = dup2(data->files.pipes[cmd][1], STDOUT_FILENO);
	if (cmd == data->n_cmds - 1)
	{
		if (data->files.outfile_fd == -1)
			exit_error(cmd, data->files.outfile, data);
		else
			dup_work = dup2(data->files.outfile_fd, STDOUT_FILENO);
	}
	if (dup_work == -1)
		finalize("Failed to execute dup2(2)", 24, data);
}

static void	exit_error(int cmd, char *file, t_data *data)
{
	char	*prefix;

	prefix = ft_strdup("bash: ");
	data->error_msg = ft_strjoin(prefix, file);
	perror(data->error_msg);
	close_fds_at_error(cmd, data);
	free_program_memory(data);
	exit (1);
}

static void	close_fds_at_error(int cmd, t_data *data)
{
	if (cmd > 0)
	{
		close(data->files.pipes[cmd][0]);
		close(data->files.pipes[cmd - 1][0]);
		if (data->n_cmds <= 2)
			close(data->files.pipes[cmd][1]);
		if (data->n_cmds > 2)
			close(data->files.pipes[cmd - 1][1]);
		close(0);
		if (data->files.infile_fd != -1)
			close(data->files.infile_fd);
	}
	else
	{
		close(data->files.pipes[cmd][0]);
		close(data->files.pipes[cmd][1]);
	}
}
