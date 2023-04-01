/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:05:13 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/29 22:16:31 by gde-mora         ###   ########.fr       */
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

static void	expander_envp_value(t_data *data, char **content) //tenho q splitar as aspas antes de splitar os $
{
	char	**mat_content;
	char	*new_content;
	t_env	*env;
	int		i;
	int		flag_env;

	mat_content = ft_split(*content, '$'); //funciona, mas vai ser o último 
	if (!mat_content || !*mat_content)
		return ;
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

void	check_envp_position(t_data *data, char **content) //isso vai ser nos lugares que tem "" !
{
	char	**mat_content;

	if (!(*content))
		return ;
	if (ft_strcmp(*content, "\"\"") == 0)
	{
		free(*content);
		*content = ft_strdup("");
		return ;
	}
	mat_content = split_with_char(*content, ' '); //checar *content antes? //teste da nova split
	
	/*print p teste
	int i = 0;
	while (mat_content[i])
	{
		ft_printf("%s\n", mat_content[i]);
		i++;
	}*/
	
	if (mat_content) //quando a split retorna NULL da error de double free
	{
		expander_content_value(data, &content, mat_content);
		free_mat(mat_content);
	}
}

void separe_quotes(t_data *data, char **content)
{
	char	**mat_content;
	char	*new_content;
	int		i;
	char	*new_str;

	if (!(*content))
		return ;
	//ft_bzero(new_mat, );
	new_str = NULL;
	new_content = NULL;
	mat_content = split_with_char(*content, '"');
//	new_mat = (char **)malloc(mat_len(mat_content) - count_chars(*content, '"') + 1);
	i = 0;
	while (mat_content[i])
	{
		if (ft_strcmp(mat_content[i], "\"") == 0)
		{
			new_str = ft_strjoin_gnl(new_str, mat_content[i]);
			i++;
			while (mat_content[i] && ft_strcmp(mat_content[i], "\"") != 0)
			{
				new_str = ft_strjoin_gnl(new_str, mat_content[i]);
				i++;
			}
			new_str = ft_strjoin_gnl(new_str, mat_content[i]);
			check_envp_position(data, &new_str);
			new_content = ft_strjoin_gnl(new_content, new_str);
			free(new_str);
			new_str = NULL;
		}
		else
		{
			//check_envp_position(data, &mat_content[i]);
			new_content = ft_strjoin_gnl(new_content, mat_content[i]);
		}
		//	ft_printf("%s\n", mat_content[i]);
//			new_mat[i] = ft_strdup(mat_content[i]);
		i++;
	}

	free(*content);
	*content = ft_strdup(new_content);
	free(new_content);
/*	i = 0;
	while (new_mat[i])
	{
		ft_printf("%s\n", new_mat[i]);
		i++;
	}*/
}
