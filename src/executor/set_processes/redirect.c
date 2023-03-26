/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:49:58 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/26 15:58:29 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	last_fd(char **files, int *files_fd);

int	redirect_input(int cmd_index, t_data *data)
{
	int		last_infile;
	t_cmd	*cmd;

	cmd = data->exec->cmds[cmd_index];
	if (cmd->infiles)
	{
		last_infile = last_fd(cmd->infiles,
				cmd->infiles_fd);
		if (last_infile != -1)
			dup2(last_infile, STDIN_FILENO);
		else
		{
			att_exit_status(1, data);
			return (0);
		}
	}
	else
	{
		if (cmd_index > 0)
			dup2(data->exec->pipes[cmd_index - 1][0], STDIN_FILENO);
	}
	if (cmd_index > 0)
		close(data->exec->pipes[cmd_index - 1][0]);
	return (1);
}

int	redirect_output(int cmd_index, t_data *data)
{
	int		last_outfile;
	t_cmd	*cmd;

	cmd = data->exec->cmds[cmd_index];
	if (cmd->outfiles)
	{
		last_outfile = last_fd(cmd->outfiles,
				cmd->outfiles_fd);
		if (last_outfile != -1)
			dup2(last_outfile, STDOUT_FILENO);
		else
		{
			att_exit_status(1, data);
			return (0);
		}
	}
	else
	{
		if (cmd_index != data->exec->cmds_amount - 1)
			dup2(data->exec->pipes[cmd_index][1], STDOUT_FILENO);
	}
	// if (cmd_index != data->exec->cmds_amount - 1)
	close(data->exec->pipes[cmd_index][1]);
	return (1);
}

static int	last_fd(char **files, int *files_fd)
{
	int	i;

	i = 0;
	while (files[i])
	{
		i++;
	}
	return (files_fd[i - 1]);
}
