/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envp_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:44:33 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/09 03:29:42 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	expand_envp_value(t_data *data, char **content)
{
	char	**mat_content;
	char	*new_content;
	t_env	*env;
	int		i;
	char	*aux;

	mat_content = split_with_char(*content, '$');
	if (!mat_content)
		return ;
	if (!*mat_content)
	{
		free(mat_content);
		mat_content = NULL;
		return ;
	}
	new_content = NULL;
	aux = NULL;
	i = 0;
	while (mat_content[i])
	{
		if (ft_strcmp(mat_content[i], "$\0") == 0)
		{
			i++;
			if (!mat_content[i])
				break ;
			if (mat_content[i][0] == '?')
			{
				aux = ft_strdup(find_env("?", data)->value);
				aux = ft_strjoin_gnl(aux, &mat_content[i][1]);
				free(mat_content[i]);
				mat_content[i] = ft_strdup(aux);
				free(aux);
				aux = NULL;
			}
			else
			{
				env = find_env(mat_content[i], data);
				if (env)
				{
					free(mat_content[i]);
					mat_content[i] = ft_strdup(env->value);
				}
				else
				{
					free(mat_content[i]);
					mat_content[i] = ft_strdup("");
				}
			}
		}
		i++;
	}
	i = 0;
	while (mat_content[i])
	{
		if (ft_strcmp(mat_content[i], "$") == 0 && !mat_content[i + 1])
			new_content = ft_strjoin_gnl(new_content, mat_content[i]);
		else if (ft_strcmp(mat_content[i], "$") != 0)
			new_content = ft_strjoin_gnl(new_content, mat_content[i]);
		i++;
	}
	free(*content);
	*content = ft_strdup(new_content);
	free(new_content);
	free_mat(mat_content);
}
