/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/11 17:34:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_only_one_built_in(t_data *data);

void	init_executor(t_data *data)
{
	if (!data->tokens)
		return ;
	get_commands_info(data);
	if (!data->exec)
		return ;
	set_here_doc(data);
	if (is_only_one_built_in(data))
		execute_built_in(data->exec->cmds[0], data);
	else
		set_processes(data);
}

static int	is_only_one_built_in(t_data *data)
{
	t_cmd	*first_cmd;

	if (data->exec->cmds_amount > 1)
		return (0);
	first_cmd = data->exec->cmds[0];
	if (is_built_in(first_cmd))
		return (1);
	return (0);
}
