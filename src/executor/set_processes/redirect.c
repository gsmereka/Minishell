/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:49:58 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/31 13:25:04 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	redirect_input(int infile, int cmd_index, t_data *data);
static int	redirect_output(int outfile, int cmd_index, t_data *data);

static int	redirect_input(int infile, int cmd_index, t_data *data)
{
	int		infile_fd;
	t_cmd	*cmd;

	cmd = data->exec->cmds[cmd_index];
	if (infile == -1)
	{
		if (cmd_index > 0)
			dup2(data->exec->pipes[cmd_index - 1][0], STDIN_FILENO);
		return (1);
	}
	infile_fd = cmd->files_fd[infile];
	if (infile_fd != -1)
		dup2(infile_fd, STDIN_FILENO);
	else
	{
		att_exit_status(1, data);
		return (0);
	}
	return (1);
}

static int	redirect_output(int outfile, int cmd_index, t_data *data)
{
	int		outfile_fd;
	t_cmd	*cmd;

	cmd = data->exec->cmds[cmd_index];
	if (outfile == -1)
	{
		if (cmd_index != data->exec->cmds_amount - 1)
			dup2(data->exec->pipes[cmd_index][1], STDOUT_FILENO);
		return (1);
	}
	outfile_fd = cmd->files_fd[outfile];
	if (outfile_fd != -1)
		dup2(outfile_fd, STDOUT_FILENO);
	else
	{
		att_exit_status(1, data);
		return (0);
	}
	return (1);
}

int	redirect(int cmd_index, t_data *data)
{
	int		i;
	int		last_outfile;
	int		last_infile;
	t_cmd	*cmd;

	i = 0;
	last_outfile = -1;
	last_infile = -1;
	cmd = data->exec->cmds[cmd_index];
	if (cmd->files)
	{
		while (cmd->files[i])
		{
			if (cmd->files_modes[i] == 0 || cmd->files_modes[i] == 1)
				last_infile = i;
			else if (cmd->files_modes[i] == 2 || cmd->files_modes[i] == 3)
				last_outfile = i;
			i++;
		}
	}
	if (!redirect_output(last_outfile, cmd_index, data))
		return (0);
	if (!redirect_input(last_infile, cmd_index, data))
		return (0);
	return (1);
}
