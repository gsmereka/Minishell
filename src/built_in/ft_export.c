/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:54 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/25 22:48:29 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int		is_valid(char *str, t_data *data);
static t_env	*is_repeated(char *str, t_data *data);
static void		add_new_environment_variable(char *str, t_data *data);
static void		att_variable(t_env *new_var, char *str, t_data *data);

void	ft_export(char **args, t_data *data)
{
	t_env	*new_var;

	if (!is_valid(args[1], data))
		return ;
	new_var = is_repeated(args[1], data);
	if (new_var)
		att_variable(new_var, args[1], data);
	if (!new_var)
		add_new_environment_variable(args[1], data);
}

static void	add_new_environment_variable(char *str, t_data *data)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	j = 0;
	while (str[j] != '=')
		j++;
	key = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(key, str, j + 1);
	value = ft_strdup(&str[j + 1]);
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
		if (ft_strncmp(variable->key, str, ft_strlen(variable->key)) == 0)
			return (variable);
		variable = variable->next;
	}
	return (NULL);
}

static void	att_variable(t_env *new_var, char *str, t_data *data)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	i = 0;
	j = 0;
	while (str[j] != '=')
		j++;
	key = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(key, str, j + 1);
	value = ft_strdup(&str[j + 1]);
	free(new_var->key);
	free(new_var->value);
	new_var->key = key;
	new_var->value = value;
}

static int	is_valid(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (str[i] == '=')
		return (0);
	i++;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
