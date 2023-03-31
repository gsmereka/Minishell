/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:54 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/31 16:23:17 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int		is_valid(char *str, t_data *data);
static void		set_variable(char *str, t_data *data);
static void		att_variable(t_env *new_var, char *key, char *value);
static void		print_vars(t_data *data);

void	ft_export(char **args, t_data *data)
{
	int	i;

	if (!args)
		return ;
	if (!args[1])
	{
		print_vars(data);
		return ;
	}
	i = 1;
	while (args[i])
	{
		if (is_valid(args[i], data))
			set_variable(args[i], data);
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
	while (str[j] != '=')
		j++;
	key = ft_calloc(j + 1, sizeof(char));
	ft_strlcpy(key, str, j + 1);
	value = ft_strdup(&str[j + 1]);
	new_var = find_env(key, data);
	if (new_var)
		att_variable(new_var, key, value);
	else
		dict_add_back(&data->dict_envp, key, value);
	free(key);
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
	return (0);
}

static void	print_vars(t_data *data)
{
	char	**envp;
	int		i;

	i = 0;
	envp = data->virtual_envp;
	if (!envp)
		return ;
	while (envp[i])
	{
		if (envp[i][0] == '?' && envp[i][1] == '=')
			i++;
		else
		{
			ft_printf("declare -x ");
			ft_printf("%s\n", envp[i]);
			i++;
		}
	}
}
