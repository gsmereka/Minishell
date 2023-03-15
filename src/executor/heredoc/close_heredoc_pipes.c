/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:05:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 23:02:01 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	close_individual_heredoc_pipes(t_cmd *cmd);

void	close_heredoc_pipes(t_data *data)
{
	t_cmd	**cmd;
	int		i;
	
	i = 0;
	cmd = data->exec->cmds;
	if (!cmd)
		return ;
	while (cmd[i])
	{
		close_individual_heredoc_pipes(cmd[i]);
		i++;
	}
}

static void	close_individual_heredoc_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->infiles)
		return ;
	while (cmd->infiles[i])
	{
		if (cmd->inputs_modes[i] == 1)
		{
			if (cmd->heredocs_pipes[i][0] != -1)
				close (cmd->heredocs_pipes[i][0]);
			if (cmd->heredocs_pipes[i][1] != -1)
				close (cmd->heredocs_pipes[i][1]);
		}
		i++;
	}
}
