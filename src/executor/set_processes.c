/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:16:01 by gsmereka          #+#    #+#             */
/*   Updated: 2022/12/29 14:21:34 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static void	set_pipes(int cmd, t_data *data);
static void	set_files(int cmd, t_data *data);
static void	set_fork(int cmd, char **envp, t_data *data);
static void	close_fds(int cmd, t_data *data);

int	set_processes(char **envp, t_data *data)
{
	int	cmd;

	cmd = 0;
	while (cmd < data->n_cmds)
	{
		set_pipes(cmd, data);
		set_files(cmd, data);
		set_fork(cmd, envp, data);
		cmd++;
	}
	return (0);
}

static void	set_pipes(int cmd, t_data *data)
{
	if (pipe(data->files.pipes[cmd]) == -1)
		finalize("Too much commands to pipe", 24, data);
}

static void	set_files(int cmd, t_data *data)
{
	if (cmd == 0)
	{
		if (data->files.here_doc == 0)
			data->files.infile_fd = open(data->files.infile, O_RDWR);
		else
			data->files.infile_fd = data->files.here_doc_pipe[0];
	}
	if (cmd == data->n_cmds - 1)
	{
		if (data->files.here_doc == 0)
			data->files.outfile_fd = open(data->files.outfile,
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (data->files.here_doc == 1)
			data->files.outfile_fd = open(data->files.outfile,
					O_RDWR | O_CREAT | O_APPEND, 0777);
	}
}

static void	set_fork(int cmd, char **envp, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		finalize("Error at use fork() function", 12, data);
	if (pid == 0)
	{
		redirect_input(cmd, data);
		redirect_output(cmd, data);
		execute(cmd, data->cmd_arg[cmd], envp, data);
	}
	else
	{
		data->process.pid[cmd] = pid;
		waitpid(data->process.pid[cmd],
			&data->process.status[cmd], WNOHANG | WUNTRACED);
		close_fds(cmd, data);
	}
}

static void	close_fds(int cmd, t_data *data)
{
	if (cmd == 1)
	{
		if (data->files.infile_fd != -1)
		{
			if (close(data->files.infile_fd) == -1)
				finalize("Fail at close file_1", 1, data);
		}
	}
	if (cmd > 0)
	{
		if (close(data->files.pipes[cmd - 1][0]) == -1)
			finalize("Fail at close a pipe output_fd", 1, data);
	}
	if (cmd == data->n_cmds - 1)
	{
		if (close(data->files.pipes[cmd][0]) == -1)
			finalize("Fail at close a pipe output_fd", 1, data);
		if (data->files.outfile_fd != -1)
		{
			if (close(data->files.outfile_fd) == -1)
				finalize("Fail at close file_2", 1, data);
		}
	}
	if (close(data->files.pipes[cmd][1]) == -1)
		finalize("Fail at close a pipe input_fd", 1, data);
}
