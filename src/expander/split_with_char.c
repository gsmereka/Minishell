/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 05:35:41 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/27 06:39:40 by gde-mora         ###   ########.fr       */
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

static void	*ft_free_mat(char **tab, size_t limit)
{
	while (limit--)
		free(tab[limit]);
	free(tab);
	return (NULL);
}

char	**split_with_char(char const *s, char c) //se der certo, passar pra lib  --aí colocar ft na frente (arq e func)
{
	char	**mat;
	size_t	len;
	size_t	size_array;
	size_t	counter;

	if (!s)
		return (NULL);
	size_array = ft_size_array(s, c) + count_chars((char *)s, c);
	mat = (char **)malloc(sizeof(char *) * (size_array + 1));
	if (!mat)
		return (NULL);
	counter = 0;
	while (counter < size_array)
	{
		len = ft_size_word(s, c);
		if (len > 0)
		{
			mat[counter] = ft_substr(s, 0, len);
			if (mat[counter++] == NULL)
				return (ft_free_mat(mat, counter - 1));
		}
		if (*s == c) //algum problema na split...
		{
			mat[counter] = malloc(2);
			mat[counter][0] = c;
			mat[counter][1] = '\0';
			counter++;
			s += 1;
		}
		s += len;
	}
	mat[counter] = NULL;
	return (mat);
}
