/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:05:13 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/06 20:33:07 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	expander_envp_value(t_data *data, char **content) //tenho q splitar as aspas antes de splitar os $
{
	char	**mat_content; //tem 6 funções aqui -- ATENÇÃO
	char	*new_content;
	t_env	*env;
	int		i;
	int		flag_env;
	char	*aux;

	mat_content = ft_split(*content, '$'); //funciona, mas vai ser o último 
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

static void	expander_simple_quotes_value(t_data *data, char **content) //vai splitar por ', mas ele n pode perder as aspas
{
	char	**mat_content;
	char	*new_content;
	int		i;
	
	mat_content = split_with_char(*content, '\'');
	if (!mat_content)
		return ;
	new_content = NULL;
	i = 0;
	while (mat_content[i])
	{
		expander_envp_value(data, &mat_content[i]);
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

static void	expander_double_quotes_value(t_data *data, char **content) //vai splitar por ', mas ele n pode perder as aspas
{
	char	**mat_content;
	char	*new_content;
	int		i;
	
	mat_content = ft_split(*content, '"');
	if (!mat_content)
		return ;
	new_content = NULL;
	i = 0;
	while (mat_content[i])
	{
		expander_simple_quotes_value(data, &mat_content[i]);
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

static void	expander_content_value(t_data *data, char ***content, char **mat_content) //nova func
{
	int		i;
	char	*new_content;

	i = 0;
	new_content = NULL;
	if (!content || !*content || !***content)
		return ;
	while (mat_content[i])
	{
		expander_double_quotes_value(data, &mat_content[i]); //aq ele vai alterar o mat content um por um
		i++;
	}
	i = 0;
	while (mat_content[i])
	{
		new_content = ft_strjoin_gnl(new_content, mat_content[i]);
		i++;
	}
	free(**content);
	**content = ft_strdup(new_content);
	free(new_content);
}

void	check_envp_position(t_data *data, char **content)
{
	char	**mat_content;

	if (!content || !(*content))
		return ;
	mat_content = split_with_char(*content, ' '); //checar *content antes? //teste da nova split
	if (mat_content) //quando a split retorna NULL da error de double free
	{
		expander_content_value(data, &content, mat_content);
		free_mat(mat_content);
	}
}

void separe_quotes(t_data *data, char **content)
{
	int		i;
	char	*str;
	char	*aux;
	char	*new_content;

	i = 0;
	str = NULL;
	new_content = NULL;
	aux = NULL;
	while ((*content)[i])
	{
		while ((*content)[i] && (*content)[i] != '\"' && (*content)[i] != '\'')
		{
			aux = malloc(2);
			aux[0] = (*content)[i];
			aux[1] = '\0';
			str = ft_strjoin_gnl(str, aux); //acho q vou ter q alocar o char
			free(aux);
		//	ft_printf("aaaaa %s\n", str);
			i++;
		}
		if (str)
		{
			check_envp_position(data, &str); //e se str nulo?
			new_content = ft_strjoin_gnl(new_content, str);
			free(str); // if (str)?   sem talvez de segfault
			str = NULL;
		}
		if ((*content)[i] && (*content)[i] == '\"')
		{
			i++;
			while ((*content)[i] && (*content)[i] != '\"')
			{
				aux = malloc(2);
				aux[0] = (*content)[i];
				aux[1] = '\0';
				str = ft_strjoin_gnl(str, aux); //acho q vou ter q alocar o char
				free(aux);
				i++;
			}
		//	i++;
			if (str)
			{
				check_envp_position(data, &str); //e se str nulo?
				new_content = ft_strjoin_gnl(new_content, str);
				free(str); // if (str)?   sem talvez de segfault
				str = NULL;
			}
		}
		if ((*content)[i] && (*content)[i] == '\'') //else if ou if?
		{
			i++;
			while ((*content)[i] && (*content)[i] != '\'')
			{
				aux = malloc(2);
				aux[0] = (*content)[i];
				aux[1] = '\0';
				str = ft_strjoin_gnl(str, aux); //acho q vou ter q alocar o char
				free(aux);
				i++;
			}
		//	i++;
		//	check_envp_position(data, &str); //e se str nulo?
			if (str)
			{
				new_content = ft_strjoin_gnl(new_content, str);
				free(str); // if (str)?   sem talvez de segfault
				str = NULL;
			}
		}
		if ((*content)[i])
			i++;
	}
	free(*content);
	if (new_content)
		*content = ft_strdup(new_content);
	else
		*content = ft_strdup("");
	free(new_content);

	/*		ler o content char por char
			armazena numa string se n for aspa dupla nem simples
			se for dupla, enquanto n achar outra dupla armazena numa string
			se for simples, enquanto n achar outra simples armazena numa string*/
}
