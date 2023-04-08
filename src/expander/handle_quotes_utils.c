/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 04:13:09 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/08 03:14:31 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	free_mat(char **mat)
{
	int	i;

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

	i = 0;
	while (mat[i])
		i++;
	return (i);
}

int	count_chars(char *content, char c) //colocar size_t?
{
	int	i;
	int	counter;

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
