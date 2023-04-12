/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:54 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/12 22:17:44 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int		is_valid(char *str, t_data *data);
static void		set_variable(char *str, t_data *data);
static void		att_variable(t_env *new_var, char *key, char *value);
static void		print_vars(t_data *data);

void	ft_export(char **args, t_data *data)
{
	int		i;
	int		status;

	if (!args)
		return ;
	if (!args[1])
		print_vars(data);
	i = 1;
	while (args[i])
	{
		status = is_valid(args[i], data);
		if (status == 1)
			set_variable(args[i], data);
		else if (status == 2)
		{
			if (!find_env(args[i], data))
			{
				dict_add_back(&data->dict_envp, args[i], "");
				find_env(args[i], data)->hidden_status = 1;
			}
		}
		i++;
	}
	att_virtual_envp(data);
}

static void	set_variable(char *str, t_data *data)
{
	int		j;
	char	*key;
	char	*value;
	t_env	*new_var;

	j = 0;
	value = NULL;
	while (str[j] != '=')
		j++;
	key = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(key, str, j + 1);
	if (str[j] == '=')
		value = ft_strdup(&str[j + 1]);
	new_var = find_env(key, data);
	if (new_var)
		att_variable(new_var, key, value);
	else
		dict_add_back(&data->dict_envp, key, value);
	if (key)
		free(key);
	if (value)
		free(value);
}

static void	att_variable(t_env *new_var, char *key, char *value)
{
	if (new_var->key)
		free(new_var->key);
	if (new_var->value)
		free(new_var->value);
	new_var->key = ft_strdup(key);
	new_var->value = ft_strdup(value);
	new_var->hidden_status = 0;
}

static int	is_valid(char *str, t_data *data)
{
	int		i;

	if (!ft_isalpha(str[0]) && str[1] != '_')
	{
		ft_export_error_msg(1, str, data);
		return (0);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_export_error_msg(1, str, data);
			return (0);
		}
		i++;
	}
	return (2);
}

static void	print_vars(t_data *data)
{
	t_env	*envp;

	envp = data->dict_envp;
	while (envp)
	{
		if (envp->hidden_status == 2)
			envp = envp->next;
		else
		{
			ft_printf("declare -x ");
			if (envp->hidden_status)
				ft_printf("%s\n", envp->key);
			else
				ft_printf("%s=\"%s\"\n", envp->key, envp->value);
			envp = envp->next;
		}
	}
}
