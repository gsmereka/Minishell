/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:03:07 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/06 15:44:34 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	search_variable(char *str, t_data *data);
static void	remove_variable(t_env *variable, t_data *data);
static void	ft_unset_error_msg(int error, char *name, t_data *data);
static int	is_valid(char *str, t_data *data);

void	ft_unset(char **args, t_data *data)
{
	int	i;

	i = 1;
	if (!args)
		return ;
	while (args[i])
	{
		if (is_valid(args[i], data))
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
		if (ft_strcmp(variable->key, str) == 0)
		{
			remove_variable(variable, data);
			break ;
		}
		variable = variable->next;
	}
}

static int	is_valid(char *str, t_data *data)
{
	int		i;

	if (!ft_isalpha(str[0]) && str[1] != '_')
	{
		ft_unset_error_msg(1, str, data);
		return (0);
	}
	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
		{
			ft_unset_error_msg(1, str, data);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	remove_variable(t_env *variable, t_data *data)
{
	t_env	*variable_in_the_back;

	if (ft_strcmp(data->dict_envp->key, variable->key) == 0)
		data->dict_envp = variable->next;
	else
	{
		variable_in_the_back = data->dict_envp;
		while (variable_in_the_back)
		{
			if (ft_strcmp(variable_in_the_back->next->key,
					variable->key) == 0)
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

static void	ft_unset_error_msg(int error, char *name, t_data *data)
{
	char		*error_msg;

	if (error == 1)
	{
		error_msg = ft_strjoin("bash: unset: `", name);
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
		error_msg = "': not a valid identifier\n";
		write(2, error_msg, ft_strlen(error_msg));
		att_exit_status(1, data);
		return ;
	}
}
