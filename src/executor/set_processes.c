/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 23:16:01 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/19 12:08:48 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_pipes(int cmd, t_data *data);
static void	set_fork(int cmd, t_data *data);
static void	close_pipes(int cmd, t_data *data);
static void	close_files(int *files);
static int	close_all_fds(t_data *data);

int	set_processes(t_data *data)
{
	int	cmd;

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
		execute(data->exec->cmds[cmd], data);
	}
	else
	{
		data->exec->pid[cmd] = pid;
		waitpid(data->exec->pid[cmd],
			&data->exec->status[cmd], WUNTRACED);
			// &data->exec->status[cmd], WNOHANG | WUNTRACED);
		close_files(data->exec->cmds[cmd]->infiles_fd);
		close_files(data->exec->cmds[cmd]->outfiles_fd);
		close_pipes(cmd, data);
	}
}

static void	close_pipes(int cmd_index, t_data *data)
{
	t_cmd	*cmd;

	cmd = data->exec->cmds[cmd_index];
	if (cmd_index > 0)
	{
		close(data->exec->pipes[cmd_index - 1][0]);
	}
	if (cmd_index == data->exec->cmds_amount - 1)
	{
		close(data->exec->pipes[cmd_index][0]);
	}
	close(data->exec->pipes[cmd_index][1]);
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

static int	close_all_fds(t_data *data)
{
	int	i;

	i = 0;
	if (!data->exec)
		return (0);
	while (data->exec->pipes[i])
	{
		close(data->exec->pipes[i][1]);
		close(data->exec->pipes[i][0]);
		close_files(data->exec->cmds[i]->infiles_fd);
		close_files(data->exec->cmds[i]->outfiles_fd);
		i++;
	}
	return (0);
}
