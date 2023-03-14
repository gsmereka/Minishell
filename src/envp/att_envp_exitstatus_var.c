/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   att_envp_exitstatus_var.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:31:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 19:00:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_env	*is_repeated(char *str, t_data *data);
static void		add_new_environment_variable(t_data *data);
static void		att_variable(t_env *new_var, t_data *data);

void	att_envp_exitstatus_var(t_data *data)
{
	t_env	*exit_status_var;

	exit_status_var = is_repeated("?", data);
	if (exit_status_var)
		att_variable(exit_status_var, data);
	if (!exit_status_var)
		add_new_environment_variable(data);
}

static void	add_new_environment_variable(t_data *data)
{
	char	*key;
	char	*value;

	key = ft_strdup("?");
	value = ft_itoa(data->exit_status);
	dict_add_back(&data->dict_envp, key, value);
	free(key);
	free(value);
}

static t_env	*is_repeated(char *str, t_data *data)
{
	t_env	*variable;

	variable = data->dict_envp;
	while (variable)
	{
		if (ft_strncmp(variable->key, str, ft_strlen(str)) == 0)
			return (variable);
		variable = variable->next;
	}
	return (NULL);
}

static void	att_variable(t_env *new_var, t_data *data)
{
	if (new_var->value)
		free(new_var->value);
	new_var->value = ft_itoa(data->exit_status);
}
