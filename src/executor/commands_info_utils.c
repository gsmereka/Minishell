/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_info_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 21:50:32 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/07 22:18:00 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	clear_cmd(t_cmd *cmd);

void	clear_commands(t_data *data)
{
	int	i;

	i = 0;
	if (!data->exec)
		return ;
	while (i < data->exec->cmds_amount)
	{
		if (data->exec->cmds)
			clear_cmd(data->exec->cmds[i]);
		i++;
	}
	if (data->exec->pipes)
		free_array_list((void **)data->exec->pipes);
	free(data->exec->cmds);
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
}


// t_cmd	*create_cmd(char *content);
// void	add_cmd(t_cmd **cmds, char *content);
// void	cmd_clear(t_cmd **cmds);

// t_cmd	*cmd_last(t_cmd *cmd)
// {
// 	t_cmd	*last_cmd;

// 	last_cmd = cmd;
// 	if (!cmd)
// 		return (cmd);
// 	while (last_cmd->next)
// 		last_cmd = last_cmd->next;
// 	return (last_cmd);
// }

// void	add_cmd(t_cmd **cmds, char *name)
// {
// 	t_cmd	*last_node;
// 	t_cmd	*new_node;

// 	if (!*cmds)
// 		*cmds = create_cmd(name);
// 	else
// 	{
// 		last_node = cmd_last(*cmds);
// 		new_node = create_cmd(name);
// 		last_node->next = new_node;
// 	}
// }

// void	cmd_clear(t_cmd **cmds)
// {
// 	if (*cmds)
// 	{
// 		cmd_clear(&(*cmds)->next);
// 		free_array_list((void **)(*cmds)->args);
// 		free((*cmds)->name);
// 		free(*cmds);
// 		*cmds = NULL;
// 	}
// }
