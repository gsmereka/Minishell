/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 22:17:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	close_files(int *files);
static void	close_fds(t_cmd *cmd, t_data *g_data);
static void	normal_execution(t_cmd *cmd, t_data *g_data);
static char	*ft_strjoin_with_free(char *s1, char *s2);

void	execute(t_cmd *cmd, t_data *g_data)
{
	if (!cmd->name)
	{
		close_fds(cmd, g_data);
		end_program(g_data);
	}
	else if (is_built_in(cmd))
	{
		execute_built_in(cmd, g_data);
		close_fds(cmd, g_data);
		end_program(g_data);
	}
	else
		normal_execution(cmd, g_data);
}

static void	normal_execution(t_cmd *cmd, t_data *g_data)
{
	int exec;

	exec = execve(cmd->name, cmd->args, g_data->virtual_envp);
	if (exec == -1)
	{
		close_fds(cmd, g_data);
		g_data->error_msg = ft_strjoin_with_free
			(ft_strdup(cmd->args[0]),
				": command not found");
		write(2, g_data->error_msg, ft_strlen(g_data->error_msg));
		free(g_data->error_msg);
		exit_error(127, "", g_data);
	}
}

static void	close_fds(t_cmd *cmd, t_data *g_data)
{
	int	i;

	i = 0;
	while (g_data->exec->pipes[i])
	{
		close(g_data->exec->pipes[i][1]);
		close(g_data->exec->pipes[i][0]);
		i++;
	}
	close_files(cmd->infiles_fd);
	close_files(cmd->outfiles_fd);
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
