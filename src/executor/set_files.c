/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:50:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/10 10:12:19 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void set_infiles(t_cmd *cmd);
static void set_outfiles(t_cmd *cmd);

void	set_files(t_cmd *cmd, t_data *data)
{
	set_infiles(cmd);
	set_outfiles(cmd);
}

static void set_infiles(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->infiles)
		return ;
	while (cmd->infiles[i])
	{
		if (cmd->inputs_modes[i] == 0)
			cmd->infiles_fd[i] = open(cmd->infiles[i], O_RDWR);
		i++;
	}
}

static void set_outfiles(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->outfiles)
		return ;
	while (cmd->outfiles[i])
	{
		if (cmd->outputs_modes[i] == 0)
			cmd->outfiles_fd[i] = open(cmd->outfiles[i],
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		else
			cmd->outfiles_fd[i] = open(cmd->outfiles[i],
					O_RDWR | O_CREAT | O_APPEND, 0777);
		i++;
	}
}
