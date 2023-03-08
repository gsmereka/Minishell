/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:18:39 by gsmereka          #+#    #+#             */
/*   Updated: 2022/12/29 14:06:10 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/pipex.h"

static void	set_cmd_names(t_data *data);
static void	set_cmd_paths(t_data *data);
static char	*test_path(int cmd, t_data *data);

int	set_cmds(t_data *data)
{
	set_cmd_names(data);
	set_cmd_paths(data);
	return (0);
}

static void	set_cmd_names(t_data *data)
{
	int	i;
	int	n_cmds;

	i = 0;
	n_cmds = data->n_cmds;
	while (i < n_cmds)
	{
		data->cmd[i] = ft_strdup(data->cmd_arg[i][0]);
		if (!data->cmd[i])
			finalize("Failed to allocate memory for a command", 12, data);
		i++;
	}
}

static void	set_cmd_paths(t_data *data)
{
	int		cmd;
	char	*cmd_path;

	cmd = 0;
	while (cmd < data->n_cmds)
	{
		cmd_path = test_path(cmd, data);
		if (cmd_path != NULL)
		{
			free(data->cmd[cmd]);
			data->cmd[cmd] = cmd_path;
		}
		cmd++;
	}
}

static char	*test_path(int cmd, t_data *data)
{
	char	*final_path;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		final_path = ft_strdup(data->paths[i]);
		final_path = ft_strjoin(final_path, "/");
		final_path = ft_strjoin(final_path, data->cmd[cmd]);
		if (!final_path)
			finalize("Failed to allocate memory for test a command path",
				12, data);
		if (access(final_path, X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}
