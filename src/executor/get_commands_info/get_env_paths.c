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

void	get_env_paths(t_data *g_data)
{
	char	*path_list;

	// FALTA TRAATAR QUANDO ALGUEM DA UNSET NO PATH
	path_list = find_env("PATH", g_data)->value;
	g_data->exec->env_paths = ft_split(path_list, ':');
	if (!g_data->exec->env_paths)
		exit_error(2, "Environment pointer have not a PATH", g_data);
}
