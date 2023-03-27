/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:05:13 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/27 04:08:32 by gde-mora         ###   ########.fr       */
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
	t_env	*env;
	int		i;
	int		flag_env;

	mat_content = ft_split(*content, '$'); //funciona, mas vai ser o último 
	new_content = NULL;
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

void	expander_quotes_value(t_data *data, char **content) //vai splitar por ', mas ele n pode perder as aspas
{
	char	**mat_content;
	char	*new_content;
	char	*aux_quote;
	int		i;
	
	mat_content = ft_split(*content, '\'');
	new_content = NULL;
	aux_quote = NULL;
	i = 0;
	while (mat_content[i])
	{
		expander_envp_value(data, &mat_content[i]);
		i++;
	}
	i = 0;
	if (*content[0] == '\'')
		new_content = ft_strjoin_gnl(new_content, "'");
	while (mat_content[i])
	{
		new_content = ft_strjoin_gnl(new_content, mat_content[i]);
		new_content = ft_strjoin_gnl(new_content, "'"); //e se n tiver no final? colocar um if antes p o começo tbm
		i++;
	}
/*	if (*content[ft_strlen(*content) - 1] != '\'') //if se for negativo antes!
	{
		aux_quote = ft_strdup(ft_strrchr(new_content, '\''));
		free(*content);
		*content = ft_strdup(aux_quote);
		free(new_content);
		free(aux_quote);
		free_mat(mat_content);
		return ;
		ft_printf("oi\n");
	}*/
	free(*content);
	*content = ft_strdup(new_content);
	free(new_content);
	free_mat(mat_content);
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
