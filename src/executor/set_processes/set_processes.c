/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:16:01 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/11 14:52:39 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	set_pipes(int cmd, t_data *data);
static void	set_fork(int cmd, t_data *data);
static void	wait_pids(t_data *data);
static void	set_execution_exit_code(t_data *data);

int	set_processes(t_data *data)
{
	int	cmd;

	cmd = 0;
	child_signals_handling(data);
	while (cmd < data->exec->cmds_amount)
	{
		if (data->need_interrupt)
			return (0);
		set_pipes(cmd, data);
		set_files(data->exec->cmds[cmd]);
		set_fork(cmd, data);
		cmd++;
	}
	wait_pids(data);
	close_all_fds(data);
	if (!data->need_interrupt)
		set_execution_exit_code(data);
	return (0);
}

static void	set_pipes(int cmd, t_data *data)
{
	if (pipe(data->exec->pipes[cmd]) == -1)
		exit_error(24, "minishell: Too much commands to pipe", data);
}

static void	set_fork(int cmd, t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_error(24, "minishell: Error at use fork() function", data);
	if (pid == 0)
	{
		if (!redirect(cmd, data))
			end_program(data);
		close_process_fds(cmd, data);
		close_cmd_heredocs(cmd, data);
		close(data->exec->pipes[cmd][0]);
		execute(data->exec->cmds[cmd], data);
	}
	else
	{
		data->exec->pid[cmd] = pid;
		close_process_fds(cmd, data);
	}
}

static void	wait_pids(t_data *data)
{
	int	cmd;

	cmd = 0;
	while (cmd < data->exec->cmds_amount)
	{
		waitpid(data->exec->pid[cmd],
			&data->exec->status[cmd], WUNTRACED);
		cmd++;
	}
}

static void	set_execution_exit_code(t_data *data)
{
	int	exit_status;
	int	cmd;

	cmd = 0;
	while (data->exec->cmds[cmd])
		cmd++;
	exit_status = WEXITSTATUS(data->exec->status[cmd - 1]);
	att_exit_status(exit_status, data);
}
