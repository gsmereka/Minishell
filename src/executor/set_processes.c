/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:16:01 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/10 14:55:30 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_pipes(int cmd, t_data *data);
static void	set_fork(int cmd, t_data *data);
static void	close_pipes(int cmd, t_data *data);
static void	close_files(int *files);

int	set_processes(t_data *data)
{
	int	cmd;

	cmd = 0;
	while (cmd < data->exec->cmds_amount)
	{
		set_pipes(cmd, data);
		set_files(data->exec->cmds[cmd], data);
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
		if (!redirect_input(cmd, data))
			end_program(data);
		if (!redirect_output(cmd, data))
			end_program(data);
		execute(data->exec->cmds[cmd], data);
	}
	else
	{
		wait(NULL);
		// data->process.pid[cmd] = pid;
		// waitpid(data->process.pid[cmd],
		// 	&data->process.status[cmd], WNOHANG | WUNTRACED);
		close_files(data->exec->cmds[cmd]->infiles_fd);
		close_files(data->exec->cmds[cmd]->outfiles_fd);
		close_pipes(cmd, data);
	}
}

static void	close_pipes(int cmd_index, t_data *data)
{
	t_cmd *cmd;

	cmd	= data->exec->cmds[cmd_index];
	if (cmd_index > 0)
	{
		if (close(data->exec->pipes[cmd_index - 1][0]) == -1)
			exit_error(24, "Fail at close a pipe output_fd", data);
	}
	if (cmd_index == data->exec->cmds_amount - 1)
	{
		if (close(data->exec->pipes[cmd_index][0]) == -1)
			exit_error(24, "Fail at close a pipe output_fd", data);
	}
	if (close(data->exec->pipes[cmd_index][1]) == -1)
		exit_error(24, "Fail at close a pipe input_fd", data);
}

static void	close_files(int *files)
{
	int	i;

	i = 0;
	if (files)
	{
		while (files[i])
		{
			if (files[i] != -1)
				close (files[i]);
			i++;
		}
	}
}
