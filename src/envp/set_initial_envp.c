/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_initial_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:51:10 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_initial_envp(char **envp, t_data *g_data)
{
	int	i;
	int	j;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		key = malloc(j + 2);
		ft_strlcpy(key, envp[i], j + 1);
		value = ft_strdup(&envp[i][j + 1]);
		dict_add_back(&g_data->dict_envp, key, value);
		free(key);
		free(value);
		i++;
	}
}
