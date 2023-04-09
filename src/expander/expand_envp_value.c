/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envp_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:44:33 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/09 03:01:54 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	expand_envp_value(t_data *data, char **content)
{
	char	**mat_content;
	char	*new_content;
	t_env	*env;
	int		i;
	int		flag_env; //vai sair
	char	*aux;

	mat_content = split_with_char(*content, '$'); //p resolver os $ sem nd(?)
	if (!mat_content)
		return ;
	if (!*mat_content)
	{
		free(mat_content);
		mat_content = NULL;
	//	free(*content);
	//	*content = ft_strdup("");
		//--isso resolve o $'oi' -- mas tira o $ sozinho (posso colocar um if para isso --tem q ser antes --mas n resolve um echo 'a'$ por ex.) -- mas e o $$? junto no if do $   se for $ ou $$, passa reto no token...?
		return ;
	}
	new_content = NULL;
	aux = NULL;
	env = data->dict_envp;
	i = 0;
//	if (*content[0] != '$')
//		i++;
	while (mat_content[i])
	{
		if (ft_strcmp(mat_content[i], "$\0") == 0)
		{
			flag_env = 0;
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
