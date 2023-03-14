/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:03:07 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	search_variable(char *str, t_data *g_data);
static void	remove_variable(t_env *variable, t_data *g_data);

void	ft_unset(char **args, t_data *g_data)
{
	int	i;

	i = 1;
	if (!args)
		return ;
	while (args[i])
	{
		search_variable(args[i], g_data);
		i++;
	}
	att_virtual_envp(g_data);
}

static void	search_variable(char *str, t_data *g_data)
{
	t_env	*variable;

	if (!str)
		return ;
	variable = g_data->dict_envp;
	while (variable)
	{
		if (ft_strncmp(variable->key, str, ft_strlen(str)) == 0)
		{
			remove_variable(variable, g_data);
			break ;
		}
		variable = variable->next;
	}
}

static void	remove_variable(t_env *variable, t_data *g_data)
{
	t_env	*variable_in_the_back;

	if (ft_strncmp(g_data->dict_envp->key, variable->key,
			ft_strlen(variable->key)) == 0)
		g_data->dict_envp = variable->next;
	else
	{
		variable_in_the_back = g_data->dict_envp;
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
