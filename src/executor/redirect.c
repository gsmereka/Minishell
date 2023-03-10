/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:49:58 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/10 10:32:47 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int last_fd(char **files, int *files_fd);

void	redirect_input(int cmd_index, t_data *data)
{
	int		last_infile;
	t_cmd	*cmd;

	cmd = data->exec->cmds[cmd_index];
	if (cmd->infiles)
	{
		last_infile = last_fd(cmd->infiles,
			cmd->infiles_fd);
		dup2(last_infile, STDIN_FILENO);
	}
	else
	{
		if (cmd_index > 0)
			dup2(data->exec->pipes[cmd_index - 1][0], STDIN_FILENO);
	}
}

void	redirect_output(int cmd_index, t_data *data)
{
	int		last_outfile;
	t_cmd	*cmd;

	cmd = data->exec->cmds[cmd_index];
	if (cmd->outfiles)
	{
		last_outfile = last_fd(cmd->outfiles,
			cmd->outfiles_fd);
		dup2(last_outfile, STDOUT_FILENO);
	}
	else
	{
		if (cmd_index != data->exec->cmds_amount - 1)
			dup2(data->exec->pipes[cmd_index][1], STDOUT_FILENO);
	}
}

static int last_fd(char **files, int *files_fd)
{
	int	i;

	i = 0;
	while (files[i])
	{
		i++;
	}
	return (files_fd[i - 1]);
}

// static void	exit_error(int cmd, char *file, t_data *data)
// {
// 	char	*prefix;

// 	prefix = ft_strdup("bash: ");
// 	data->error_msg = ft_strjoin(prefix, file);
// 	perror(data->error_msg);
// 	close_fds_at_error(cmd, data);
// 	free_program_memory(data);
// 	exit (1);
// }

// static void	close_fds_at_error(int cmd_index, t_data *data)
// {
// 	if (cmd > 0)
// 	{
// 		close(data->files.pipes[cmd_index][0]);
// 		close(data->files.pipes[cmd_index - 1][0]);
// 		if (data->n_cmds <= 2)
// 			close(data->files.pipes[cmd_index][1]);
// 		if (data->n_cmds > 2)
// 			close(data->files.pipes[cmd_index - 1][1]);
// 		close(0);
// 		if (data->files.infile_fd != -1)
// 			close(data->files.infile_fd);
// 	}
// 	else
// 	{
// 		close(data->files.pipes[cmd_index][0]);
// 		close(data->files.pipes[cmd_index][1]);
// 	}
// }
