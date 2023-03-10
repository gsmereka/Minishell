/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:50:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/10 14:35:45 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void set_infiles(t_cmd *cmd, t_data *data);
static void set_outfiles(t_cmd *cmd, t_data *data);
static void	error_msg(char *file, t_data *data);

void	set_files(t_cmd *cmd, t_data *data)
{
	set_infiles(cmd, data);
	set_outfiles(cmd, data);
}

static void set_infiles(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	if (!cmd->infiles)
		return ;
	while (cmd->infiles[i])
	{
		if (cmd->inputs_modes[i] == 0)
		{
			cmd->infiles_fd[i] = open(cmd->infiles[i], O_RDWR);
			if (cmd->infiles_fd[i] == -1)
				error_msg(cmd->infiles[i], data);
		}
		i++;
	}
}

static void set_outfiles(t_cmd *cmd, t_data *data)
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
		if (cmd->outfiles_fd[i] == -1)
			error_msg(cmd->outfiles[i], data);
		i++;
	}
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
