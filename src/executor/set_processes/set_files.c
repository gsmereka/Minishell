/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:50:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/29 20:52:38 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	set_infiles(t_cmd *cmd);
static int	set_outfiles(t_cmd *cmd);
static void	error_msg(char *file);

void	set_files(t_cmd *cmd)
{
	if (!set_outfiles(cmd))
		return ;
	if (!set_infiles(cmd))
		return ;
}

static int	set_infiles(t_cmd *cmd)
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
				error_msg(cmd->infiles[i]);
				return (0);
			}
		}
		else if (cmd->inputs_modes[i] == 1)
		{
			if (cmd->heredocs_pipes[i][0])
				cmd->infiles_fd[i] = cmd->heredocs_pipes[i][0];
		}
		i++;
	}
	return (1);
}

static int	set_outfiles(t_cmd *cmd)
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
			error_msg(cmd->outfiles[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	error_msg(char *file)
{
	char	*prefix;
	char	*error_msg;

	prefix = ft_strdup("bash: ");
	error_msg = ft_strjoin(prefix, file);
	free(prefix);
	perror(error_msg);
	free(error_msg);
	error_msg = NULL;
}
