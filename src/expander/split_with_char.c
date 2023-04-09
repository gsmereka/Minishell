/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 05:35:41 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/08 03:37:21 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static size_t	ft_size_array(const char *s, char c)
{
	int		is_new_word;
	size_t	words;

	is_new_word = 0;
	words = 0;
	while (*s)
	{
		if (is_new_word == 0 && *s != c)
		{
			is_new_word = 1;
			words++;
		}
		else if (is_new_word == 1 && *s == c)
			is_new_word = 0;
		s++;
	}
	return (words);
}

static size_t	ft_size_word(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_free_mat(char **tab, size_t limit)
{
	while (limit--)
		free(tab[limit]);
	free(tab);
	return (0);
}

static size_t	save_mat(char ***mat, char *s, char c, size_t size)
{
	size_t	len;
	size_t	counter;

	counter = 0;
	while (counter < size)
	{
		len = ft_size_word(s, c);
		if (len > 0)
		{
			(*mat)[counter] = ft_substr(s, 0, len);
			if ((*mat)[counter++] == NULL)
				return (ft_free_mat(*mat, counter - 1));
		}
		if (*s == c)
		{
			(*mat)[counter] = malloc(2);
			(*mat)[counter][0] = c;
			(*mat)[counter++][1] = '\0';
			s += 1;
		}
		s += len;
	}
	return (counter);
}

char	**split_with_char(char const *s, char c)
{
	char	**mat;
	size_t	size_array;
	size_t	counter;

	if (!s)
		return (NULL);
	size_array = ft_size_array(s, c) + count_chars((char *)s, c);
	mat = (char **)malloc(sizeof(char *) * (size_array + 1));
	if (!mat)
		return (NULL);
	counter = save_mat(&mat, (char *)s, c, size_array);
	mat[counter] = NULL;
	return (mat);
}
