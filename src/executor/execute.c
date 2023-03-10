/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:17:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/10 15:32:52 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	close_fds(t_cmd *cmd, t_data *data);
static int	is_built_in(t_cmd *cmd);
static void	normal_execution(t_cmd *cmd, t_data *data);
static char	*ft_strjoin_with_free(char *s1, char *s2);

void	execute(t_cmd *cmd, t_data *data)
{
	if (is_built_in(cmd))
	{
		execute_built_in(cmd, data);
		close_fds(cmd, data);
		end_program(data);
	}
	else
		normal_execution(cmd, data);
}

static void	normal_execution(t_cmd *cmd, t_data *data)
{
	int exec;

	if (!cmd->name)
	{
		close_fds(cmd, data);
		end_program(data);
	}
	exec = execve(cmd->name, cmd->args, data->virtual_envp);
	if (exec == -1)
	{
		close_fds(cmd, data);
		data->error_msg = ft_strjoin_with_free
			(ft_strdup(cmd->args[0]),
				": command not found");
		write(2, data->error_msg, ft_strlen(data->error_msg));
		free(data->error_msg);
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
	// if (cmd == data->n_cmds - 1 && cmd->outfile_fd != -1)
	// 	close(cmd->outfile_fd);
	// if (cmd->infile_fd != -1)
	// 	close(cmd->infile_fd);
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

static int	is_built_in(t_cmd *cmd)
{
	char	**args;

	args = cmd->args;
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
