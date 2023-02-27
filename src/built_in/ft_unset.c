/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:03:07 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/26 18:10:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	remove_variable(t_env *variable, t_data *data);

void	ft_unset(char **args, t_data *data)
{
	t_env	*variable;

	if (!args[0])
		return ;
	variable = data->dict_envp;
	while (variable)
	{
		if (ft_strncmp(variable->key, args[0], ft_strlen(variable->key)) == 0)
		{
			remove_variable(variable, data);
			att_virtual_envp(data);
			break ;
		}
		variable = variable->next;
	}
}

static void	remove_variable(t_env *variable, t_data *data)
{
	t_env	*variable_in_the_back;

	if (ft_strncmp(data->dict_envp->key, variable->key,
			ft_strlen(variable->key)) == 0)
		data->dict_envp = variable->next;
	else
	{
		variable_in_the_back = data->dict_envp;
		while (variable_in_the_back->next)
		{
			if (ft_strncmp(variable_in_the_back->next->key,
					variable->key, ft_strlen(variable->key)) == 0)
			{
				variable_in_the_back->next = variable->next;
				break ;
			}
			variable_in_the_back = variable_in_the_back->next;
		}
	}
	free(variable->key);
	free(variable->value);
	free(variable);
}
