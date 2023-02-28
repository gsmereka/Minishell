/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:03:07 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/27 23:15:18 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	search_variable(char *str, t_data *data);
static void	remove_variable(t_env *variable, t_data *data);

void	ft_unset(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!args)
		return ;
	while (args[i])
	{
		search_variable(args[i], data);
		i++;
	}
	att_virtual_envp(data);
}

static void	search_variable(char *str, t_data *data)
{
	t_env	*variable;

	if (!str)
		return ;
	variable = data->dict_envp;
	while (variable)
	{
		if (ft_strncmp(variable->key, str, ft_strlen(str)) == 0)
		{
			remove_variable(variable, data);
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
		while (variable_in_the_back)
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
