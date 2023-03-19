/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:05:13 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/19 20:22:16 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_env_value(char *mat_token, t_env *aux_env, int flag_env)
{

	
	check_spaces();
	
	while (aux_env) // toda a parte da substituição q funciona. O problema é quando tem espaços // e se tiver aspas???? eu tenho q tirar elas antes? e ignorar elas tbm 
	{
		if (ft_strcmp(aux_env->key, &mat_token[i][1]) == 0) 
		{
			new_content = ft_strjoin_gnl(new_content, aux_env->value);
			flag_env = 1;
		}
		aux_env = aux_env->next;
	}
	if (flag_env == 0)
		new_content = ft_strjoin_gnl(new_content, " ");
}

void	expander_envp_value(t_data *data, char ***content, char **mat_token)
{
	char	*new_content;
	t_env	*aux_env;
	int		i;
	int		flag_env;

	aux_env = data->dict_envp;
	i = 0;
	new_content = NULL;
	while (mat_token[i])
	{
		flag_env = 0;
		aux_env = data->dict_envp;
		if (mat_token[i][0] == '$')
		{
			//problema se tiver espaço... split no espaço :/ --pq n posso substituir td se tiver espaço -- e as aspas tbm tem q parar
			set_env_value(&mat_token[i], aux_env, flag_env);
		}
		else
			new_content = ft_strjoin_gnl(new_content, mat_token[i]);
		i++;
	}
	free(**content);
	**content = ft_strdup(new_content);
	free(new_content);
}

void	check_envp_position_in_token(t_data *data, char **content) //+ 25 linhas
{
	char	**mat_content;
	int		i;
	char	**mat_token;

	mat_content = ft_split(*content, '$'); //checar *content antes?
	if (!mat_content || !*mat_content) //assim?
		return ;
	mat_token = NULL;
	i = 0;
	if (mat_len(mat_content) > 1) // ft_strlen ** e *... warning
	{
		mat_token = (char **)malloc(sizeof(char *) * (mat_len(mat_content) + 1)); //colocar verificação aqui?
		mat_token[i] = ft_strdup(mat_content[i]);
		i++;
		while (mat_content[i])
		{
			mat_token[i] = ft_strdup("$");
			mat_token[i] = ft_strjoin_gnl(mat_token[i], mat_content[i]);
			i++;
		}
		mat_token[i] = NULL;
		if (mat_token)
		{
			expander_envp_value(data, &content, mat_token);
			free_mat(mat_token);
		}
	}
	free_mat(mat_content);
}
