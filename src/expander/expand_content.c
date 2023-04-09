/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:05:13 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/08 03:12:50 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	expand_simple_quotes_value(t_data *data, char **content)
{
	char	**mat_content;
	char	*new_content;
	int		i;

	mat_content = split_with_char(*content, '\'');
	if (!mat_content)
		return ;
	new_content = NULL;
	i = -1;
	while (mat_content[++i])
		expand_envp_value(data, &mat_content[i]);
	i = -1;
	while (mat_content[++i])
		new_content = ft_strjoin_gnl(new_content, mat_content[i]);
	free(*content);
	*content = ft_strdup(new_content);
	free(new_content);
	free_mat(mat_content);
}

static void	expand_double_quotes_value(t_data *data, char **content)
{
	char	**mat_content;
	char	*new_content;
	int		i;

	mat_content = ft_split(*content, '"');
	if (!mat_content)
		return ;
	new_content = NULL;
	i = -1;
	while (mat_content[++i])
		expand_simple_quotes_value(data, &mat_content[i]);
	i = -1;
	while (mat_content[++i])
		new_content = ft_strjoin_gnl(new_content, mat_content[i]);
	free(*content);
	*content = ft_strdup(new_content);
	free(new_content);
	free_mat(mat_content);
}

static void	expand_content(t_data *data, char ***content, char **mat_content)
{
	int		i;
	char	*new_content;

	new_content = NULL;
	if (!content || !*content || !***content)
		return ;
	i = -1;
	while (mat_content[++i])
		expand_double_quotes_value(data, &mat_content[i]);
	i = -1;
	while (mat_content[++i])
		new_content = ft_strjoin_gnl(new_content, mat_content[i]);
	free(**content);
	**content = ft_strdup(new_content);
	free(new_content);
}

void	check_envp_position(t_data *data, char **content)
{
	char	**mat_content;

	if (!content || !(*content))
		return ;
	mat_content = split_with_char(*content, ' ');
	if (mat_content)
	{
		expand_content(data, &content, mat_content);
		free_mat(mat_content);
	}
}
