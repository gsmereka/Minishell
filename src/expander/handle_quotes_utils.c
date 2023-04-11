/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 04:13:09 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/11 04:58:26 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_mat(char **mat)
{
	int	i;

	if (!mat)
		return ;
	if (!*mat)
	{
		free(mat);
		mat = NULL;
		return ;
	}
	i = 0;
	while (mat[i])
	{
		free(mat[i]);
		i++;
	}
	free(mat);
	mat = NULL;
}

size_t	mat_len(char **mat)
{
	size_t	i;

	if (!mat || !*mat)
		return (0);
	i = 0;
	while (mat[i])
		i++;
	return (i);
}

size_t	count_chars(char *content, char c)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	if (!content || !*content)
		return (0);
	while (content[i])
	{
		if (content[i] == c)
			counter++;
		i++;
	}
	return (counter);
}

int	is_null_cmd(char *content)
{
	char	simple_quote;
	char	double_quote;
	char	*str1;
	char	*str2;
	int		is_null;

	simple_quote = '\'';
	double_quote = '"';
	str1 = ft_strtrim(content, &simple_quote);
	str2 = ft_strtrim(content, &double_quote);
	is_null = 0;
	if (ft_strlen(str1) < 1 || ft_strlen(str2) < 1)
		is_null = 1;
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	return (is_null);
}
