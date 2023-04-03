/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:50:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/03 17:28:41 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	setup_files(t_cmd *cmd);
static void	error_msg(char *file);

void	set_files(t_cmd *cmd)
{
	if (!cmd->files)
		return ;
	setup_files(cmd);
}

static void	setup_files(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->files[i])
	{
		if (cmd->files_modes[i] == 0)
			cmd->files_fd[i] = open(cmd->files[i], O_RDWR);
		else if (cmd->files_modes[i] == 1)
		{
			if (cmd->heredocs_pipes[i][0])
				cmd->files_fd[i] = cmd->heredocs_pipes[i][0];
		}
		else if (cmd->files_modes[i] == 2)
			cmd->files_fd[i] = open(cmd->files[i],
					O_RDWR | O_CREAT | O_TRUNC, 0777);
		else if (cmd->files_modes[i] == 3)
			cmd->files_fd[i] = open(cmd->files[i],
					O_RDWR | O_CREAT | O_APPEND, 0777);
		if (cmd->files_fd[i] == -1)
		{
			error_msg(cmd->files[i]);
			break ;
		}
		i++;
	}
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
