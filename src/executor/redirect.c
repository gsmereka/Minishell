/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:49:58 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/09 19:29:59 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	redirect_input(int cmd, t_data *data)
{
	if (data->exec->cmds[cmd]->infiles)
	{
		// open
	}
	else
	{
		if (cmd > 0)
			dup2(data->exec->pipes[cmd - 1][0], STDIN_FILENO);
	}
}

void	redirect_output(int cmd, t_data *data)
{
	if (cmd != data->exec->cmds_amount - 1)
		dup2(data->exec->pipes[cmd][1], STDOUT_FILENO);
}
