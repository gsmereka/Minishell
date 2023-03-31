/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:10:06 by gsmereka          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/02 11:10:58 by gsmereka         ###   ########.fr       */
=======
/*   Updated: 2023/03/30 20:14:14 by gsmereka         ###   ########.fr       */
>>>>>>> executor_merged
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*find_env(char *key, t_data *data)
{
	t_env	*envp;

	envp = data->dict_envp;
	while (envp)
	{
		if (ft_strncmp(envp->key, key, ft_strlen(key)) == 0)
			break ;
		envp = envp->next;
	}
	return (envp);
}
