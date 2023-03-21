/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_set_cmds_paths.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:18:39 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/21 14:04:50 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	*test_path(int cmd, t_data *data);

int	set_cmds_paths(t_data *data)
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
	return (1);
}

static char	*test_path(int cmd, t_data *data)
{
	char	*final_path;
	int		i;

	i = 0;
	if (!data->exec->cmds[cmd]->name)
		return (NULL);
	if (!data->exec->env_paths)
		return (NULL);
	while (data->exec->env_paths[i])
	{
		final_path = ft_strjoin(data->exec->env_paths[i], "/");
		final_path = ft_strjoin_with_free
			(final_path, data->exec->cmds[cmd]->name);
		if (!final_path)
		{
			att_exit_status(12, data);
			ft_putstr_fd("failed to allocate memory for command path", 2);
			return (NULL);
		}
		if (access(final_path, X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}
