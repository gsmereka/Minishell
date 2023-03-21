/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:16:01 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/21 14:58:06 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	set_pipes(int cmd, t_data *data);
static void	set_fork(int cmd, t_data *data);
static void	wait_pids(t_data *data);

int	set_processes(t_data *data)
{
	int	cmd;
	int	exit_status;

	cmd = 0;
	data->exec->pid = ft_calloc(data->exec->cmds_amount + 1, sizeof(int));
	data->exec->status = ft_calloc(data->exec->cmds_amount + 1, sizeof(int));
	while (cmd < data->exec->cmds_amount)
	{
		if (data->exec->need_interrupt)
			return (0);
		set_pipes(cmd, data);
		set_files(data->exec->cmds[cmd], data);
		set_fork(cmd, data);
		cmd++;
	}
	wait_pids(data);
	close_all_fds(data);
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
		close_child_pipes_fds(cmd, data);
		execute(data->exec->cmds[cmd], data);
	}
	else
	{
		data->exec->pid[cmd] = pid;
		close_files_fds(data->exec->cmds[cmd]->infiles_fd);
		close_files_fds(data->exec->cmds[cmd]->outfiles_fd);
		close_parent_pipes_fds(cmd, data);
	}
}

static void	wait_pids(t_data *data)
{
	int	cmd;
	int	exit_status;

	cmd = 0;
	while (cmd < data->exec->cmds_amount)
	{
		waitpid(data->exec->pid[cmd],
			&data->exec->status[cmd], WUNTRACED);
		cmd++;
	}
	exit_status = WEXITSTATUS(data->exec->status[cmd - 1]);
	att_exit_status(exit_status, data);
}
