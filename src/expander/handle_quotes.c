/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:05:13 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/26 20:52:05 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*void	check_quotes(char *mat_token)
{
	char	**quotes;
	int		i;

	quotes = ft_split(mat_token, ' ');
	i = 0;
	while (aux_spaces_token[i])
	{
		if (aux_spaces_token[i][0] == '$')
			find_envp_value(aux_spaces_token[i]);
		i++;
	}
}*/

void	expander_envp_value(t_data *data, char **content) //tenho q splitar as aspas antes de splitar os $
{
	char	**mat_content;
	char	*new_content;
	char	*aux_content;
	t_env	*env;
	int		i;
	int		flag_env;

	mat_content = ft_split(*content, '$'); //funciona, mas vai ser o último 
	new_content = NULL;
	aux_content = NULL;
	env = data->dict_envp;
	i = 0;
	if (*content[0] != '$')
		i++;
	while (mat_content[i])
	{
		flag_env = 0;
		env = data->dict_envp;
		while (env)
		{
			if (ft_strcmp(mat_content[i], env->key) == 0)
			{
				free(mat_content[i]);
				mat_content[i] = ft_strdup(env->value);
				flag_env = 1;
				break ; 
			}
		/*	else if (ft_strlen(mat_content[i]) - 1 > 0)
			{
				if (mat_content[i][ft_strlen(mat_content[i]) - 1] == '\'') // e se o len < 0 nessa comparação...
				{
					aux_content = malloc(ft_strlen(mat_content[i]) - 1); //para o caso das aspas '$oi' .... mas n resolve '$oi'a
					int j = 0; //arrumar norma aq
					while (j < ft_strlen(mat_content[i]) - 1)
					{
						aux_content[j] = mat_content[i][j];
						j++;
					}
					aux_content[j] = '\0';
					if (ft_strcmp(aux_content, env->key) == 0)
					{
						free(mat_content[i]);
						mat_content[i] = ft_strdup(env->value);
						mat_content[i] = ft_strjoin_gnl(mat_content[i], "'");
						free(aux_content);
						aux_content = NULL;
						flag_env = 1;
						break ; 
					}
				}
			}*/
			env = env->next;
		}
		if (flag_env == 0)
		{
			free(mat_content[i]);
			mat_content[i] = ft_strdup("");
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

void	expander_quotes_value(t_data *data, **content) //vai splitar por ', mas ele n pode perder as aspas
{
	
}

void	expander_content_value(t_data *data, char ***content, char **mat_content) //nova func
{
	int		i;
	char	*new_content;

	i = 0;
	new_content = NULL;
	while (mat_content[i])
	{
		expander_quotes_value(data, &mat_content[i]); //aq ele vai alterar o mat content um por um
		i++;
	}
	i = 0;
	while (mat_content[i])
	{
		new_content = ft_strjoin_gnl(new_content, mat_content[i]);
		new_content = ft_strjoin_gnl(new_content, " "); //pq fiz split por espaço
		i++;
	}
	free(**content);
	**content = ft_strdup(new_content);
	free(new_content);
}

void	check_envp_position_in_token(t_data *data, char **content) //nova func
{
	char	**mat_content;

	mat_content = ft_split(*content, ' '); //checar *content antes?
	if (mat_content)
	{
		expander_content_value(data, &content, mat_content);
		free_mat(mat_content);
	}
}
