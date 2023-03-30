/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_execution_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:50:32 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/30 13:51:28 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	clear_cmd(t_cmd *cmd);
static void	free_intern_cmds(t_data *data);
static void	free_intern_pipes(t_data *data);

void	clear_execution_data(t_data *data)
{
	if (!data->exec)
		return ;
	if (data->exec->pid)
		free(data->exec->pid);
	if (data->exec->status)
		free(data->exec->status);
	free_intern_cmds(data);
	free_intern_pipes(data);
	if (data->exec->env_paths)
		free_array_list((void **)data->exec->env_paths);
	free(data->exec);
	data->exec = NULL;
}

static void	free_intern_cmds(t_data *data)
{
	int	i;

	i = 0;
	if (!data->exec->cmds)
		return ;
	while (i < data->exec->cmds_amount)
	{
		if (data->exec->cmds[i])
			clear_cmd(data->exec->cmds[i]);
		i++;
	}
	if (data->exec->cmds)
		free(data->exec->cmds);
}

static void	free_intern_pipes(t_data *data)
{
	int	i;

	i = 0;
	if (!data->exec->pipes)
		return ;
	while (i < data->exec->cmds_amount)
	{
		if (data->exec->pipes[i])
			free(data->exec->pipes[i]);
		i++;
	}
	free(data->exec->pipes);
}

static void	clear_cmd(t_cmd *cmd)
{
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
		free_array_list((void **)cmd->args);
	if (cmd->files_fd)
		free(cmd->files_fd);
	if (cmd->files)
		free_array_list((void **)cmd->files);
	if (cmd->files_modes)
		free(cmd->files_modes);
	if (cmd->heredocs_pipes)
		free_array_list((void **)cmd->heredocs_pipes);
	if (cmd)
		free(cmd);
}
