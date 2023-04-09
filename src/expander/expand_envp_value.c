/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_envp_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:44:33 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/09 04:11:52 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	save_content(char ***content, char ***mat_content)
{
	int		i;
	char	*new_content;

	i = 0;
	new_content = NULL;
	while ((*mat_content)[i])
	{
		if (ft_strcmp((*mat_content)[i], "$") == 0 && !(*mat_content)[i + 1])
			new_content = ft_strjoin_gnl(new_content, (*mat_content)[i]);
		else if (ft_strcmp((*mat_content)[i], "$") != 0)
			new_content = ft_strjoin_gnl(new_content, (*mat_content)[i]);
		i++;
	}
	free(**content);
	**content = ft_strdup(new_content);
	free(new_content);
	free_mat(*mat_content);
}

static void	save_special_content(t_data *data, char **content)
{
	char	*aux;

	aux = ft_strdup(find_env("?", data)->value);
	aux = ft_strjoin_gnl(aux, &(*content)[1]);
	free(*content);
	*content = ft_strdup(aux);
	free(aux);
	aux = NULL;
}

static void	save_normal_content(t_data *data, char **content)
{
	t_env	*env;

	env = find_env(*content, data);
	if (env)
	{
		free(*content);
		*content = ft_strdup(env->value);
	}
	else
	{
		free(*content);
		*content = ft_strdup("");
	}
}

static int	check_mat(char ***mat_content)
{
	if (!*mat_content)
		return (0);
	if (!**mat_content)
	{
		free(*mat_content);
		*mat_content = NULL;
		return (0);
	}
	return (1);
}

void	expand_envp_value(t_data *data, char **content)
{
	char	**mat_content;
	int		i;

	mat_content = split_with_char(*content, '$');
	if (!check_mat(&mat_content))
		return ;
	i = -1;
	while (mat_content[++i])
	{
		if (ft_strcmp(mat_content[i], "$\0") == 0)
		{
			i++;
			if (!mat_content[i])
				break ;
			if (mat_content[i][0] == '?')
				save_special_content(data, &mat_content[i]);
			else
				save_normal_content(data, &mat_content[i]);
		}
	}
	save_content(&content, &mat_content);
}
