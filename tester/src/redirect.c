/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:27:29 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/23 22:19:07 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static void	exit_error(int cmd, char *file, t_data *data);
static void	close_fds_at_error(int cmd, t_data *data);

void	redirect_input(int test, t_data *data)
{
	int	dup_work;

	dup_work = dup2(data->input_tests_fd[test], 0);
	if (dup_work == -1)
		exit_error(24, "Failed to execute dup2(2)", data);
}

void	redirect_output(int test, t_data *data)
{
	int	dup_work;

	dup_work = dup2(data->user_outputs_fd[test], 1);
	if (dup_work == -1)
		exit_error(24, "Failed to execute dup2(2)", data);
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
