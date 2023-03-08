/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:18:39 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/08 10:57:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	*test_path(int cmd, t_data *data);

void	set_cmds_paths(t_data *data)
{
	int		cmd;
	char	*cmd_path;

	cmd = 0;
	while (cmd < data->exec->cmds_amount)
	{
		cmd_path = test_path(cmd, data);
		if (cmd_path != NULL)
		{
			free(data->exec->cmds[cmd]->name);
			data->exec->cmds[cmd]->name = cmd_path;
		}
		cmd++;
	}
}

static char	*test_path(int cmd, t_data *data)
{
	char	*final_path;
	int		i;

	i = 0;
	while (data->exec->env_paths[i])
	{
		final_path = ft_strdup(data->exec->env_paths[i]);
		final_path = ft_strjoin(final_path, "/");
		final_path = ft_strjoin(final_path, data->exec->cmds[cmd]->name);
		if (!final_path)
			exit_error(12, "Failed to allocate memory for test a command path", data);
		if (access(final_path, X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}
