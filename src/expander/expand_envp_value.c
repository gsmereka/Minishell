/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envp_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:44:33 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/08 03:09:50 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	expand_envp_value(t_data *data, char **content)
{
	char	**mat_content;
	char	*new_content;
	t_env	*env;
	int		i;
	int		flag_env;
	char	*aux;

	mat_content = ft_split(*content, '$');
	if (!mat_content)
		return ;
	if (!*mat_content)
	{
		free(mat_content);
	//	*content = ft_strdup("");
		mat_content = NULL;
		return ;
	}

	//deletar o $ nos casos $'oi' ...? como?
	
	new_content = NULL;
	aux = NULL;
	env = data->dict_envp;
	i = 0;
	if (*content[0] != '$')
		i++;
	while (mat_content[i])
	{
		flag_env = 0;
		env = data->dict_envp;
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
			while (env)
			{
				if (ft_strcmp(mat_content[i], env->key) == 0) //usar find env
				{
					free(mat_content[i]);
					mat_content[i] = ft_strdup(env->value);
					flag_env = 1;
					break ; 
				}
				env = env->next;
			}
			if (flag_env == 0)
			{
				free(mat_content[i]);
				mat_content[i] = ft_strdup("");
			}
		}
		i++;
	}
	i = 0;
	while (mat_content[i])
	{
		new_content = ft_strjoin_gnl(new_content, mat_content[i]);
		i++;
	}
	free(*content);
	*content = ft_strdup(new_content);
	free(new_content);
	free_mat(mat_content);
}
