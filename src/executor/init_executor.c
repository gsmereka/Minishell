/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/10 20:31:26 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	do_not_need_fork(t_data *data);
static void	set_built_in(t_data *data);

void	init_executor(t_data *data)
{
	if (!data->tokens || data->need_interrupt)
		return ;
	get_commands_info(data);
	if (!data->exec)
		return ;
	if (!set_heredoc(data))
		return ;
	if (do_not_need_fork(data))
		set_built_in(data);
	else
		set_processes(data);
}

static int	do_not_need_fork(t_data *data)
{
	t_cmd	*first_cmd;

	if (data->exec->cmds_amount > 1)
		return (0);
	first_cmd = data->exec->cmds[0];
	if (!first_cmd->args)
		return (0);
	if (ft_strcmp(first_cmd->args[0], "env") == 0)
		return (0);
	else if (ft_strcmp(first_cmd->args[0], "echo") == 0)
		return (0);
	if (is_built_in(first_cmd))
		return (1);
	return (0);
}

static void	set_built_in(t_data *data)
{
	att_exit_status(0, data);
	if (data->exec->cmds[0]->files)
	{
		data->output_save_fd = dup(1);
		data->input_save_fd = dup(0);
		set_files(data->exec->cmds[0]);
		if (!redirect(0, data))
		{
			dup2(data->output_save_fd, 1);
			dup2(data->input_save_fd, 0);
			return ;
		}
	}
	execute_built_in(data->exec->cmds[0], data);
	dup2(data->output_save_fd, 1);
	dup2(data->input_save_fd, 0);
	close(data->input_save_fd);
	close(data->output_save_fd);
	close_files_fds(data->exec->cmds[0]->files,
		data->exec->cmds[0]->files_fd);
	close_cmd_heredocs(0, data);
}
