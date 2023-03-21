/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:19:11 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/21 15:11:30 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	close_all_fds(t_data *data)
{
	int	i;

	i = 0;
	if (!data->exec)
		return (0);
	if (!data->exec->pipes)
		return (0);
	while (data->exec->pipes[i])
	{
		if (data->exec->pipes[i][1] != -1)
			close(data->exec->pipes[i][1]);
		if (data->exec->pipes[i][0] != -1)
			close(data->exec->pipes[i][0]);
		if (data->exec->cmds)
		{
			close_files_fds(data->exec->cmds[i]->infiles_fd);
			close_files_fds(data->exec->cmds[i]->outfiles_fd);
		}
		i++;
	}
	return (0);
}

void	close_parent_pipes_fds(int cmd_index, t_data *data)
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

void	close_child_pipes_fds(int cmd_index, t_data *data)
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

void	close_all_child_files_fds(int cmd_index, t_data *data)
{
	t_cmd	*cmd;
	int		fd_index;

	cmd = data->exec->cmds[cmd_index];
	if (cmd->infiles_fd)
	{
		fd_index = 0;
		while (cmd->infiles_fd[fd_index + 1])
		{
			close(cmd->infiles_fd[fd_index]);
			fd_index++;
		}
	}
	if (cmd->outfiles_fd)
	{
		fd_index = 0;
		while (cmd->outfiles_fd[fd_index + 1])
		{
			close(cmd->outfiles_fd[fd_index]);
			fd_index++;
		}
	}
}

void	close_files_fds(int *files)
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
