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

void	get_env_paths(t_data *data)
{
	char	*path_list;
	t_env	*env_paths;

	env_paths = find_env("PATH", data);
	if (!env_paths)
	{
		data->exec->env_paths = NULL;
		return ;
	}
	path_list = find_env("PATH", data)->value;
	data->exec->env_paths = ft_split(path_list, ':');
	if (!data->exec->env_paths)
		exit_error(2, "Environment pointer have not a PATH", data);
}
