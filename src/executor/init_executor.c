/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_only_one_built_in(t_data *g_data);

void	init_executor(t_data *g_data)
{
	if (!g_data->tokens)
		return ;
	get_commands_info(g_data);
	if (!g_data->exec)
		return ;
	set_here_doc(g_data);
	if (is_only_one_built_in(g_data))
		execute_built_in(g_data->exec->cmds[0], g_data);
	else
		set_processes(g_data);
}

static int	is_only_one_built_in(t_data *g_data)
{
	t_cmd	*first_cmd;

	if (g_data->exec->cmds_amount > 1)
		return (0);
	first_cmd = g_data->exec->cmds[0];
	if (is_built_in(first_cmd))
		return (1);
	return (0);
}
