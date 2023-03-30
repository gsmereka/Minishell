/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 16:19:58 by gsmereka          #+#    #+#             */
/*   Updated: 2022/12/29 14:06:22 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	get_env_paths(t_data *data)
{
	char	*path_list;
	t_env	*env_paths;

	env_paths = find_env("PATH", data);
	if (!env_paths)
	{
		data->exec->env_paths = NULL;
		return (1);
	}
	path_list = find_env("PATH", data)->value;
	data->exec->env_paths = ft_split(path_list, ':');
	if (!data->exec->env_paths)
	{
		att_exit_status(12, data);
		ft_putstr_fd("Fail at split paths", 2);
		return (0);
	}
	return (1);
}
