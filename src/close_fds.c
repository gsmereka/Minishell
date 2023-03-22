/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:19:11 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/22 16:52:12 by gsmereka         ###   ########.fr       */
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
			close_files_fds(data->exec->cmds[i]->infiles,
				data->exec->cmds[i]->infiles_fd);
			close_files_fds(data->exec->cmds[i]->outfiles,
				data->exec->cmds[i]->outfiles_fd);
		}
		i++;
	}
	return (0);
}

void	close_parent_pipes_fds(int cmd_index, t_data *data)
{
	t_cmd	*cmd;

	if (!data->exec)
		return ;
	if (data->exec->cmds)
		return ;
	cmd = data->exec->cmds[cmd_index];
	close_cmd_heredoc_pipes(cmd);
	close_cmd_pipes(cmd_index, data);
	close_files_fds(cmd->infiles, cmd->infiles_fd);
	close_files_fds(cmd->outfiles, cmd->outfiles_fd);
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

void	close_files_fds(char **paths, int *files)
{
	int	i;

	i = 0;
	if (files && paths)
	{
		while (paths[i])
		{
			if (files[i] != -1)
				close (files[i]);
			i++;
		}
	}
}
