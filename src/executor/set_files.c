/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:50:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/20 12:51:40 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	set_infiles(t_cmd *cmd, t_data *data);
static int	set_outfiles(t_cmd *cmd, t_data *data);
static void	error_msg(char *file, t_data *data);

void	set_files(t_cmd *cmd, t_data *data)
{
	if (!set_infiles(cmd, data))
		return ;
	if (!set_outfiles(cmd, data))
		return ;
}

static int	set_infiles(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (!cmd->infiles)
		return (1);
	while (cmd->infiles[i])
	{
		if (cmd->inputs_modes[i] == 0)
		{
			cmd->infiles_fd[i] = open(cmd->infiles[i], O_RDWR);
			if (cmd->infiles_fd[i] == -1)
			{
				error_msg(cmd->infiles[i], data);
				return (0);
			}
		}
		else if (cmd->inputs_modes[i] == 1)
		{
			// todas as entradas dos pipes vao ser fechadas na hora da leitura dos heredocs.
			if (cmd->heredocs_pipes[i][0])
				cmd->infiles_fd[i] = cmd->heredocs_pipes[i][0];
		}
		i++;
	}
	return (1);
}

static int	set_outfiles(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (!cmd->outfiles)
		return (1);
	while (cmd->outfiles[i])
	{
		if (cmd->outputs_modes[i] == 0)
			cmd->outfiles_fd[i] = open(cmd->outfiles[i],
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		else
			cmd->outfiles_fd[i] = open(cmd->outfiles[i],
					O_RDWR | O_CREAT | O_APPEND, 0777);
		if (cmd->outfiles_fd[i] == -1)
		{
			error_msg(cmd->outfiles[i], data);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	error_msg(char *file, t_data *data)
{
	char	*prefix;

	prefix = ft_strdup("bash: ");
	data->error_msg = ft_strjoin(prefix, file);
	free(prefix);
	perror(data->error_msg);
	free(data->error_msg);
	data->error_msg = NULL;
}
