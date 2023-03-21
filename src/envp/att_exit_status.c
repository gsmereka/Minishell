/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   att_exit_status.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 18:31:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/20 22:17:03 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_env	*is_repeated(char *str, t_data *data);
static void		add_new_environment_variable(int exit_status, t_data *data);
static void		att_variable(int exit_status, t_env *new_var, t_data *data);

void	att_exit_status(int exit_status, t_data *data)
{
	t_env	*exit_status_var;

	if (data->exit_status == exit_status && exit_status != 0)
		return ;
	data->exit_status = exit_status;
	exit_status_var = find_env("?", data);
	if (exit_status_var)
		att_variable(exit_status, exit_status_var, data);
	if (!exit_status_var)
		add_new_environment_variable(exit_status, data);
}

static void	add_new_environment_variable(int exit_status, t_data *data)
{
	char	*key;
	char	*value;

	key = ft_strdup("?");
	value = ft_itoa(exit_status);
	dict_add_back(&data->dict_envp, key, value);
	free(key);
	free(value);
}

static void	att_variable(int exit_status, t_env *new_var, t_data *data)
{
	if (new_var->value)
		free(new_var->value);
	new_var->value = ft_itoa(exit_status);
}
