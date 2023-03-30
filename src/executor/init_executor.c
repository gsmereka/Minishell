/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/29 20:52:53 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	do_not_need_fork(t_data *data);
static void	set_built_in(t_data *data);

void	init_executor(t_data *data)
{
	if (!data->tokens)
		return ;
	get_commands_info(data);
	if (!data->exec)
		return ;
	if (!set_heredoc(data))
		return ;
	if (do_not_need_fork(data))
		set_built_in(data);
	else
		set_processes(data);
}

static int	do_not_need_fork(t_data *data)
{
	t_cmd	*first_cmd;

	if (data->exec->cmds_amount > 1)
		return (0);
	first_cmd = data->exec->cmds[0];
	if (!first_cmd->args)
		return (0);
	if (ft_strncmp(first_cmd->args[0], "env",
			ft_strlen(first_cmd->args[0])) == 0)
		return (0);
	if (is_built_in(first_cmd))
		return (1);
	return (0);
}

static void	set_built_in(t_data *data)
{
	set_files(data->exec->cmds[0]);
	if (!redirect_output(0, data))
		return ;
	if (!redirect_input(0, data))
		return ;
	execute_built_in(data->exec->cmds[0], data);
}
