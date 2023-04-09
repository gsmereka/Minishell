/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 04:13:09 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/09 04:19:28 by gde-mora         ###   ########.fr       */
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
