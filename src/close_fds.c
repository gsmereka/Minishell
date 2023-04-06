/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:19:11 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/06 20:10:52 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	close_all_fds(t_data *data)
{
	int	i;

	i = 0;
	if (!data->exec)
		return (0);
	if (!data->exec->pipes)
		return (0);
	close_heredoc_pipes(data);
	while (data->exec->pipes[i])
	{
		if (data->exec->pipes[i][1] != -1)
			close(data->exec->pipes[i][1]);
		if (data->exec->pipes[i][0] != -1)
			close(data->exec->pipes[i][0]);
		if (data->exec->cmds)
		{
			close_files_fds(data->exec->cmds[i]->files,
				data->exec->cmds[i]->files_fd);
		}
		i++;
	}
	return (0);
}

void	close_process_fds(int cmd_index, t_data *data)
{
	t_cmd	*cmd;

	if (!data->exec)
		return ;
	if (!data->exec->cmds)
		return ;
	cmd = data->exec->cmds[cmd_index];
	close(data->exec->pipes[cmd_index][1]);
	close_cmd_pipes(cmd_index, data);
	close_cmd_heredocs(cmd_index, data);
	close_files_fds(cmd->files, cmd->files_fd);
}

void	close_cmd_heredocs(int cmd_index, t_data *data)
{
	t_cmd	*cmd;
	int		i;
	int		last_heredoc;

	cmd = data->exec->cmds[cmd_index];
	if (!cmd)
		return ;
	if (!cmd->heredocs_pipes || !cmd->files_modes || !cmd->files)
		return ;
	i = 0;
	last_heredoc = 0;
	while (cmd->files[i])
	{
		if (cmd->files_modes[i] == 1)
		{
			if (cmd->heredocs_pipes[i][0] != -1)
				close(cmd->heredocs_pipes[i][0]);
			if (cmd->heredocs_pipes[i][1] != -1)
				close(cmd->heredocs_pipes[i][1]);
		}
		i++;
	}
}

void	close_cmd_pipes(int cmd_index, t_data *data)
{
	int	*current_pipe;
	int	*previous_pipe;

	current_pipe = data->exec->pipes[cmd_index];
	if (cmd_index > 0)
		previous_pipe = data->exec->pipes[cmd_index - 1];
	if (cmd_index > 0)
		close(previous_pipe[0]);
	if (cmd_index == data->exec->cmds_amount - 1)
		close(current_pipe[0]);
	close(current_pipe[1]);
}

void	close_files_fds(char **files, int *files_fds)
{
	int	i;

	i = 0;
	if (files_fds && files)
	{
		while (files[i])
		{
			if (files_fds[i] != -1)
				close (files_fds[i]);
			i++;
		}
	}
}
