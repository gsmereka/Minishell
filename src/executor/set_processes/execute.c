/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:17:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/25 11:36:23 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	close_files(int *files);
static void	close_fds(t_cmd *cmd, t_data *data);
static void	normal_execution(t_cmd *cmd, t_data *data);

void	execute(t_cmd *cmd, t_data *data)
{
	if (!cmd->name)
	{
		close_fds(cmd, data);
		end_program(data);
	}
	else if (is_built_in(cmd))
	{
		execute_built_in(cmd, data);
		close_fds(cmd, data);
		end_program(data);
	}
	else
	{
		att_exit_status(0, data);
		normal_execution(cmd, data);
	}
}

static void	normal_execution(t_cmd *cmd, t_data *data)
{
	int		exec;
	char	*error_msg;

	exec = execve(cmd->name, cmd->args, data->virtual_envp);
	if (exec == -1)
	{
		close_fds(cmd, data);
		error_msg = ft_strjoin_with_free
			(ft_strdup(cmd->args[0]),
				": command not found");
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
		exit_error(127, "", data);
	}
}

static void	close_fds(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (data->exec->pipes[i])
	{
		close(data->exec->pipes[i][1]);
		close(data->exec->pipes[i][0]);
		i++;
	}
	close_files(cmd->infiles_fd);
	close_files(cmd->outfiles_fd);
	close(1);
	close(0);
}

static void	close_files(int *files)
{
	int	i;

	i = 0;
	if (files)
	{
		while (files[i])
		{
			if (files[i] != -1)
				close (files[i]);
			i++;
		}
	}
}
