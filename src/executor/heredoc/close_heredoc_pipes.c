/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:05:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/30 13:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

void	close_heredoc_pipes(t_data *data)
{
	t_cmd	**cmd;
	int		i;

	i = 0;
	if (!data->exec)
		return ;
	cmd = data->exec->cmds;
	if (!cmd)
		return ;
	while (i < data->exec->cmds_amount)
	{
		close_cmd_heredoc_pipes(cmd[i]);
		i++;
	}
}

void	close_cmd_heredoc_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->files)
		return ;
	while (cmd->files[i])
	{
		if (!cmd->files_modes)
			break ;
		if (cmd->files_modes[i] == 1)
		{
			if (!cmd->heredocs_pipes)
				return ;
			if (cmd->heredocs_pipes[i])
			{
				if (cmd->heredocs_pipes[i][0] != -1)
					close (cmd->heredocs_pipes[i][0]);
				if (cmd->heredocs_pipes[i][1] != -1)
					close (cmd->heredocs_pipes[i][1]);
			}
		}
		i++;
	}
}
