/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   att_virtual_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:43:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/02 19:42:04 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	calculate_envp_size(t_data *data);
static void	fill_virtual_envp(t_data *data);

void	att_virtual_envp(t_data *data)
{
	int		size;

	if (data->virtual_envp)
		free_array_list((void **)data->virtual_envp);
	size = calculate_envp_size(data);
	data->virtual_envp = ft_calloc(size + 1, sizeof(char *));
	if (!data->virtual_envp)
		exit_error(12, "fail at alloc virtual envp memory", data);
	fill_virtual_envp(data);
}

static int	calculate_envp_size(t_data *data)
{
	t_env	*envp;
	int		size;

	size = 0;
	envp = data->dict_envp;
	while (envp)
	{
		size++;
		envp = envp->next;
	}
	return (size);
}

static void	fill_virtual_envp(t_data *data)
{
	t_env	*dict_envp;
	char	*key;
	int		i;

	i = 0;
	dict_envp = data->dict_envp;
	while (dict_envp)
	{
		if (!dict_envp->hidden_status)
		{
			key = ft_strdup(dict_envp->key);
			data->virtual_envp[i] = ft_strjoin_with_free(key, "=");
			data->virtual_envp[i]
				= ft_strjoin_with_free(data->virtual_envp[i], dict_envp->value);
			if (!data->virtual_envp[i])
				exit_error(12, "fail at fill virtual envp memory", data);
			i++;
		}
		dict_envp = dict_envp->next;
	}
}
