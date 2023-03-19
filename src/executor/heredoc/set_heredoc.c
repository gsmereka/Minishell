/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:05:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 21:36:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	alloc_heredoc_pipes(t_data *data);
static int	setup_individual_heredoc_pipes(t_cmd *cmd);
static int	alloc_individual_heredoc_pipes(t_cmd *cmd);

int	set_heredoc(t_data *data)
{
	
	// heredoc_signals_handling(data);
	alloc_heredoc_pipes(data);
	if (!heredoc_cmd_loop(data))
		return (0);
	return (1);
}

static int	alloc_heredoc_pipes(t_data *data)
{
	t_cmd	**cmd;
	int		i;

	i = 0;
	cmd = data->exec->cmds;
	if (!cmd)
		return (0);
	while (cmd[i])
	{
		if (!alloc_individual_heredoc_pipes(cmd[i]))
			return (0);
		if (!setup_individual_heredoc_pipes(cmd[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	alloc_individual_heredoc_pipes(t_cmd *cmd)
{
	int	size;

	size = 0;
	if (!cmd->infiles)
		return (0);
	while (cmd->infiles[size])
		size++;
	cmd->heredocs_pipes = ft_calloc(size + 1, sizeof(int *));
	if (!cmd->heredocs_pipes)
		return (0);
	return (1);
}

static int	setup_individual_heredoc_pipes(t_cmd *cmd)
{
	int	doc;

	doc = 0;
	if (!cmd->heredocs_pipes)
		return (0);
	while (cmd->heredocs_pipes[doc])
	{
		cmd->heredocs_pipes[doc] = ft_calloc(2, sizeof(int));
		if (!cmd->heredocs_pipes[doc])
			return (0);
		cmd->heredocs_pipes[doc][0] = -1;
		cmd->heredocs_pipes[doc][1] = -1;
		doc++;
	}
	return (1);
}
