/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_info_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:50:32 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	clear_cmd(t_cmd *cmd);
static void	free_intern_cmds(t_data *g_data);
static void	free_intern_pipes(t_data *g_data);

void	clear_commands(t_data *g_data)
{
	if (!g_data->exec)
		return ;
	free_intern_cmds(g_data);
	free_intern_pipes(g_data);
	if (g_data->exec->env_paths)
		free_array_list((void **)g_data->exec->env_paths);
	free(g_data->exec);
	g_data->exec = NULL;
}

static void	free_intern_cmds(t_data *g_data)
{
	int	i;

	i = 0;
	if (!g_data->exec->cmds)
		return ;
	while (i < g_data->exec->cmds_amount)
	{
		if (g_data->exec->cmds[i])
			clear_cmd(g_data->exec->cmds[i]);
		i++;
	}
	if (g_data->exec->cmds)
		free(g_data->exec->cmds);
}

static void	free_intern_pipes(t_data *g_data)
{
	int	i;

	i = 0;
	if (!g_data->exec->pipes)
		return ;
	while (i < g_data->exec->cmds_amount)
	{
		if (g_data->exec->pipes[i])
			free(g_data->exec->pipes[i]);
		i++;
	}
	free(g_data->exec->pipes);
}

static void	clear_cmd(t_cmd *cmd)
{
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
		free_array_list((void **)cmd->args);
	if (cmd->infiles_fd)
		free(cmd->infiles_fd);
	if (cmd->outfiles_fd)
		free(cmd->outfiles_fd);
	if (cmd->infiles)
		free_array_list((void **)cmd->infiles);
	if (cmd->outfiles)
		free_array_list((void **)cmd->outfiles);
	if (cmd->inputs_modes)
		free(cmd->inputs_modes);
	if (cmd->outputs_modes)
		free(cmd->outputs_modes);
	if (cmd->heredocs_pipes)
		free_array_list((void **)cmd->heredocs_pipes);
	if (cmd)
		free(cmd);
}
