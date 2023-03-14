/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   att_envp_exitstatus_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:31:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_env	*is_repeated(char *str, t_data *g_data);
static void		add_new_environment_variable(t_data *g_data);
static void		att_variable(t_env *new_var, t_data *g_data);

void	att_envp_exitstatus_var(t_data *g_data)
{
	t_env	*exit_status_var;

	exit_status_var = is_repeated("?", g_data);
	if (exit_status_var)
		att_variable(exit_status_var, g_data);
	if (!exit_status_var)
		add_new_environment_variable(g_data);
}

static void	add_new_environment_variable(t_data *g_data)
{
	char	*key;
	char	*value;

	key = ft_strdup("?");
	value = ft_itoa(g_data->exit_status);
	dict_add_back(&g_data->dict_envp, key, value);
	free(key);
	free(value);
}

static t_env	*is_repeated(char *str, t_data *g_data)
{
	t_env	*variable;

	variable = g_data->dict_envp;
	while (variable)
	{
		if (ft_strncmp(variable->key, str, ft_strlen(str)) == 0)
			return (variable);
		variable = variable->next;
	}
	return (NULL);
}

static void	att_variable(t_env *new_var, t_data *g_data)
{
	if (new_var->value)
		free(new_var->value);
	new_var->value = ft_itoa(g_data->exit_status);
}
