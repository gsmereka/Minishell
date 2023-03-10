/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:17:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/09 22:15:40 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	close_fds_at_error(int cmd, t_data *data);
static int	is_built_in(int cmd, t_data *data);
static void	normal_execution(int cmd, char **cmd_args, t_data *data);
static char	*ft_strjoin_with_free(char *s1, char *s2);

void	execute(int cmd, char **cmd_args, t_data *data)
{
	int		exec;

	if (is_built_in(cmd, data))
	{
		execute_built_in(cmd, data);
		close_fds_at_error(cmd, data);
		end_program(data);
	}
	else
		normal_execution(cmd, cmd_args, data);
}

static void	normal_execution(int cmd, char **cmd_args, t_data *data)
{
	int exec;

	exec = execve(data->exec->cmds[cmd]->name,
			cmd_args, data->virtual_envp);
	if (exec == -1)
	{
		close_fds_at_error(cmd, data);
		data->error_msg = ft_strjoin_with_free
			(ft_strdup(data->exec->cmds[cmd]->args[0]),
				": command not found");
		write(2, data->error_msg, ft_strlen(data->error_msg));
		free(data->error_msg);
		exit_error(127, "", data);
	}
}

static void	close_fds_at_error(int cmd, t_data *data)
{
	// if (cmd == data->n_cmds - 1 && data->exec->outfile_fd != -1)
	// 	close(data->exec->outfile_fd);
	// if (data->exec->infile_fd != -1)
	// 	close(data->exec->infile_fd);
	if (cmd > 0)
		close(data->exec->pipes[cmd - 1][0]);
	close(data->exec->pipes[cmd][1]);
	close(data->exec->pipes[cmd][0]);
	close(1);
	close(0);
}

static char	*ft_strjoin_with_free(char *s1, char *s2)
{
	char	*new_s;
	int		s1_size;
	int		s2_size;
	int		i;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 | !s2)
		return (NULL);
	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	new_s = (char *)malloc((s1_size + s2_size + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	while (i < (s1_size + s2_size + 1))
	{
		if (i < s1_size)
			new_s[i] = s1[i];
		else
			new_s[i] = s2[i - s1_size];
		i++;
	}
	free(s1);
	return ((char *)new_s);
}

static int	is_built_in(int cmd, t_data *data)
{
	char	**args;

	args = data->exec->cmds[cmd]->args;
	if (!args || !args[0])
		return (0);
	else if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (1);
	return (0);
}
