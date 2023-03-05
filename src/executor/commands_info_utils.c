/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_info_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:36:59 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/05 13:41:36 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_cmd	*create_cmd(char *content);
void	add_cmd(t_cmd **cmds, char *content);
void	cmd_clear(t_cmd **cmds);

t_cmd	*create_cmd(char *name)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	return (new_node);
}

t_cmd	*cmd_last(t_cmd *cmd)
{
	t_cmd	*last_cmd;

	last_cmd = cmd;
	if (!cmd)
		return (cmd);
	while (last_cmd->next)
		last_cmd = last_cmd->next;
	return (last_cmd);
}

void	add_cmd(t_cmd **cmds, char *name)
{
	t_cmd	*last_node;
	t_cmd	*new_node;

	if (!*cmds)
		*cmds = create_cmd(name);
	else
	{
		last_node = cmd_last(*cmds);
		new_node = create_cmd(name);
		last_node->next = new_node;
	}
}

void	cmd_clear(t_cmd **cmds)
{
	if (*cmds)
	{
		cmd_clear(&(*cmds)->next);
		free_array_list((void **)(*cmds)->args);
		free((*cmds)->name);
		free(*cmds);
		*cmds = NULL;
	}
}
