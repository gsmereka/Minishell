/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:17:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/26 18:49:33 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	print_execution_error(char *prefix, char *name, char *sufix);
static void	normal_execution(t_cmd *cmd, t_data *data);
static void	close_execution_fds(t_data *data);
static void	identify_error(char *name, t_data *data);

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
	int		error_status;

	att_exit_status(0, data);
	exec = execve(cmd->name, cmd->args, data->virtual_envp);
	if (exec == -1)
	{
		close_execution_fds(data);
		identify_error(cmd->args[0], data);
		end_program(data);
	}
}

static void	identify_error(char *name, t_data *data)
{
	struct stat	dir_info;

	dir_info = (struct stat){0};
	stat(name, &dir_info);
	if (name[0] != '/' && ft_strncmp(name, "./", 2)
		&& ft_strncmp(name, "..", 2))
	{
		print_execution_error("", name, ": command not found\n");
		att_exit_status(127, data);
	}
	else if (access(name, F_OK) == -1)
	{
		print_execution_error("bash: ", name, ": No such file or directory\n");
		att_exit_status(127, data);
	}
	else if (S_ISDIR(dir_info.st_mode))
	{
		print_execution_error("bash: ", name, ": Is a directory\n");
		att_exit_status(126, data);
	}
	else
	{
		print_execution_error("bash: ", name, ": Permission denied\n");
		att_exit_status(126, data);
	}
}

static void	print_execution_error(char *prefix, char *name, char *sufix)
{
	char	*error_msg;

	error_msg = ft_strjoin(prefix, name);
	error_msg = ft_strjoin_with_free(error_msg, sufix);
	write(2, error_msg, ft_strlen(error_msg));
	if (error_msg)
		free(error_msg);
}

static void	close_execution_fds(t_data *data)
{
	close_all_fds(data);
	close(0);
	close(1);
}
