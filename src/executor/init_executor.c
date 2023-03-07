/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/07 20:00:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	split_cmd_tokens(t_data *data);

void	init_executor(t_data *data)
{
	get_commands_info(data);
	split_cmd_tokens(data);
}

static void	split_cmd_tokens(t_data *data)
{
	t_token	*token;
	t_cmd	**cmd;
	int		cmd_index;

	cmd_index = 0;
	token = data->tokens;
	cmd = data->exec->cmds;
	while (token)
	{
		token = format_cmd(token, cmd[cmd_index], data);
		cmd_index++;
	}
}
