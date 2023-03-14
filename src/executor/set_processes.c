/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:16:01 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_pipes(int cmd, t_data *g_data);
static void	set_fork(int cmd, t_data *g_data);
static void	close_pipes(int cmd, t_data *g_data);
static void	close_files(int *files);

int	set_processes(t_data *g_data)
{
	int	cmd;

	cmd = 0;
	while (cmd < g_data->exec->cmds_amount)
	{
		set_pipes(cmd, g_data);
		set_files(g_data->exec->cmds[cmd], g_data);
		set_fork(cmd, g_data);
		cmd++;
	}
	return (0);
}

static void	set_pipes(int cmd, t_data *g_data)
{
	if (pipe(g_data->exec->pipes[cmd]) == -1)
		exit_error(24, "Too much commands to pipe", g_data);
}

static void	set_fork(int cmd, t_data *g_data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_error(24, "Error at use fork() function", g_data);
	if (pid == 0)
	{
		if (!redirect_input(cmd, g_data))
			end_program(g_data);
		if (!redirect_output(cmd, g_data))
			end_program(g_data);
		execute(g_data->exec->cmds[cmd], g_data);
	}
	else
	{
		wait(NULL);
		// g_data->process.pid[cmd] = pid;
		// waitpid(g_data->process.pid[cmd],
		// 	&g_data->process.status[cmd], WNOHANG | WUNTRACED);
		close_files(g_data->exec->cmds[cmd]->infiles_fd);
		close_files(g_data->exec->cmds[cmd]->outfiles_fd);
		close_pipes(cmd, g_data);
	}
}

static void	close_pipes(int cmd_index, t_data *g_data)
{
	t_cmd *cmd;

	cmd	= g_data->exec->cmds[cmd_index];
	if (cmd_index > 0)
	{
		if (close(g_data->exec->pipes[cmd_index - 1][0]) == -1)
			exit_error(24, "Fail at close a pipe output_fd", g_data);
	}
	if (cmd_index == g_data->exec->cmds_amount - 1)
	{
		if (close(g_data->exec->pipes[cmd_index][0]) == -1)
			exit_error(24, "Fail at close a pipe output_fd", g_data);
	}
	if (close(g_data->exec->pipes[cmd_index][1]) == -1)
		exit_error(24, "Fail at close a pipe input_fd", g_data);
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
