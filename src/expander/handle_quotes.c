/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:05:13 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/25 04:51:36 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	find_envp_value()
{

	
	//check_spaces();
	
	
}

/*void	check_spaces(char *mat_token)
{
	char	**aux_spaces_token;
	int		i;

	aux_spaces_token = ft_split(mat_token, ' ');
	i = 0;
	while (aux_spaces_token[i])
	{
		if (aux_spaces_token[i][0] == '$')
			find_envp_value(aux_spaces_token[i]);
		i++;
	}
}*/

void	expander_envp_value(t_data *data, char ***content, char **mat_token)
{
	//t_expander *expander;
	char	*new_content;
	t_env	*aux_env;
	int		i;
	char	**aux_spaces_token;
	int		j;

	aux_env = data->dict_envp;
	i = 0;
	new_content = NULL;
	while (mat_token[i])
	{
		//flag_env = 0;
		aux_env = data->dict_envp;
		if (mat_token[i][0] == '$') //tenho q dar split por espaço antes então, e depois por $
		{
			j = 0;
			//problema se tiver espaço... split no espaço :/ --pq n posso substituir td se tiver espaço -- e as aspas tbm tem q parar
			aux_spaces_token = ft_split(mat_token[i], ' '); //mas n ta impedindo de apagar se dentro a env tiver entre ''
			if (!aux_spaces_token)
				return ;
			while (aux_spaces_token[j])
			{
				//set_env_value(&mat_token[i], aux_env, flag_env);
				while (aux_env) // toda a parte da substituição q funciona. O problema é quando tem espaços // e se tiver aspas???? eu tenho q tirar elas antes? e ignorar elas tbm 
				{
					if (ft_strcmp(aux_env->key, &aux_spaces_token[j][1]) == 0) 
						new_content = ft_strjoin_gnl(new_content, aux_env->value);
					aux_env = aux_env->next;
				}
				if (aux_spaces_token[j][0] != '$')
					new_content = ft_strjoin_gnl(new_content, aux_spaces_token[j]);
			//	if (mat_len(aux_spaces_token) > 1)
					new_content = ft_strjoin_gnl(new_content, " ");
				j++;
			}
			free_mat(aux_spaces_token);
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
	if (mat_len(mat_content) > 0) // ft_strlen ** e *... warning
	{
		mat_token = (char **)malloc(sizeof(char *) * (mat_len(mat_content) + 1)); //colocar verificação aqui?
		if ((*content)[0] != '$')
		{
			mat_token[i] = ft_strdup(mat_content[i]); //arruma "teste$miau" mas quebra "$miau$miau"
			i++;
		}
		while (mat_content[i])
		{
			mat_token[i] = ft_strdup("$");
			mat_token[i] = ft_strjoin_gnl(mat_token[i], mat_content[i]);
			//ft_printf("%s\n", mat_token[i]);
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
