/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:16:01 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/26 16:11:57 by gsmereka         ###   ########.fr       */
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
	while (cmd < data->exec->cmds_amount)
	{
		if (data->exec->need_interrupt)
			return (0);
		set_pipes(cmd, data);
		set_files(data->exec->cmds[cmd]);
		set_fork(cmd, data);
		cmd++;
	}
	close_all_fds(data);
	wait_pids(data);
	set_execution_exit_code(data);
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

	child_signals_handling(data);
	pid = fork();
	if (pid == -1)
		exit_error(24, "Error at use fork() function", data);
	if (pid == 0)
	{
		if (!redirect_input(cmd, data))
			end_program(data);
		if (!redirect_output(cmd, data))
			end_program(data);
		// close_all_fds(data); Preciso botar uma função que libere os outros pipes e os arquivos não utilizados.
		execute(data->exec->cmds[cmd], data);
	}
	else
	{
		data->exec->pid[cmd] = pid;
		close(data->exec->pipes[cmd][1]);
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
