/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:16:01 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/09 19:40:20 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_pipes(int cmd, t_data *data);
static void	set_fork(int cmd, t_data *data);
static void	close_fds(int cmd, t_data *data);

int	set_processes(t_data *data)
{
	int	cmd;

	cmd = 0;
	while (cmd < data->exec->cmds_amount)
	{
		set_pipes(cmd, data);
		set_files(cmd, data);
		set_fork(cmd, data);
		cmd++;
	}
	return (0);
}

static void	set_pipes(int cmd, t_data *data)
{
	if (pipe(data->exec->pipes[cmd]) == -1)
		exit_error(24, "Too much commands to pipe", data);
}

static void	set_fork(int cmd, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_error(24, "Error at use fork() function", data);
	if (pid == 0)
	{
		redirect_input(cmd, data);
		redirect_output(cmd, data);
		execute(cmd, data->exec->cmds[cmd]->args, data);
	}
	else
	{
		wait(NULL);
		// data->process.pid[cmd] = pid;
		// waitpid(data->process.pid[cmd],
		// 	&data->process.status[cmd], WNOHANG | WUNTRACED);
		close_fds(cmd, data);
	}
}

static void	close_fds(int cmd, t_data *data)
{
	// if (cmd == 1)
	// {
	// 	if (data->exec->infile_fd != -1)
	// 	{
	// 		if (close(data->exec->infile_fd) == -1)
	// 			exit_error(24, "Fail at close file_1", data);
	// 	}
	if (cmd > 0)
	{
		if (close(data->exec->pipes[cmd - 1][0]) == -1)
			exit_error(24, "Fail at close a pipe output_fd", data);
	}
	if (cmd == data->exec->cmds_amount - 1)
	{
		if (close(data->exec->pipes[cmd][0]) == -1)
			exit_error(24, "Fail at close a pipe output_fd", data);
		// if (data->exec->outfile_fd != -1)
		// {
		// 	if (close(data->exec->outfile_fd) == -1)
		// 		exit_error(24, "Fail at close file_2", data);
		// }
	}
	if (close(data->exec->pipes[cmd][1]) == -1)
		exit_error(24, "Fail at close a pipe input_fd", data);
}
