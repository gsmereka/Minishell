/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:17:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/25 11:49:18 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	normal_execution(t_cmd *cmd, t_data *data);
static void	close_execution_fds(t_data *data);

void	execute(t_cmd *cmd, t_data *data)
{
	if (!cmd->name)
	{
		close_execution_fds(data);
		end_program(data);
	}
	else if (is_built_in(cmd))
	{
		execute_built_in(cmd, data);
		close_execution_fds(data);
		end_program(data);
	}
	else
		normal_execution(cmd, data);
}

static void	normal_execution(t_cmd *cmd, t_data *data)
{
	int		exec;
	char	*error_msg;

	att_exit_status(0, data);
	exec = execve(cmd->name, cmd->args, data->virtual_envp);
	if (exec == -1)
	{
		close_execution_fds(data);
		error_msg = ft_strjoin_with_free
			(ft_strdup(cmd->args[0]),
				": command not found");
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
		exit_error(127, "", data);
	}
}

static void	close_execution_fds(t_data *data)
{
	close_all_fds(data);
	close(0);
	close(1);
}
