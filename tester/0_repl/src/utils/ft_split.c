/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 21:38:47 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/25 12:44:31 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tester.h"

static size_t	ft_split_size(const char *s, char c)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (*s && *s == c)
		s++;
	while (s[i])
	{
		if (i == 0)
			size++;
		else if (s[i - 1] == c && s[i] != c)
			size++;
		i++;
	}
	return (size);
}

static void	*free_mem(char **arr, int i)
{
	while (--i > -1)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static	size_t	ft_next_c(const char *s, char c, unsigned int i)
{
	size_t	next_c;

	next_c = 0;
	while (s[i] != c && s[i])
	{
		next_c++;
		i++;
	}
	return (next_c);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	size_t			size;
	size_t			position;
	size_t			next_c;
	char			**new_s;

	i = 0;
	position = 0;
	size = ft_split_size(s, c);
	new_s = malloc((size + 1) * sizeof(char *));
	if (!new_s || !s)
		return (NULL);
	while (position < size)
	{
		while (s[i] == c)
			i++;
		next_c = ft_next_c(s, c, i);
		new_s[position] = ft_substr(s, i, next_c);
		if (new_s[position] == NULL)
			free_mem(new_s, i);
		position++;
		i += next_c + 1;
	}
	new_s[size] = NULL;
	return (new_s);
}
