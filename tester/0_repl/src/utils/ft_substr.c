/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 19:24:31 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/25 12:44:37 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tester.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size);

static	size_t	ft_subs_size(size_t s_size, size_t start, size_t len)
{
	unsigned int	subs_size;

	if (start < s_size)
	{
		subs_size = s_size - start;
	}
	if (start >= s_size)
	{
		subs_size = 0;
	}
	if (subs_size > len)
	{
		subs_size = len;
	}
	return (subs_size);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	subs_size;
	size_t	s_size;

	if (!s)
		return (NULL);
	s_size = strlen(s);
	subs_size = ft_subs_size(s_size, start, len);
	subs = (char *)calloc(subs_size + 1, sizeof(char));
	if (!subs)
		return (NULL);
	if (subs_size == 0)
		subs[0] = 0;
	else
		ft_strlcpy(subs, &s[start], subs_size + 1);
	return (subs);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	count;

	count = 0;
	while ((src[count] != '\0') && (count + 1 < size))
	{
		dst[count] = src[count];
		count++;
	}
	if (size > 0)
		dst[count] = '\0';
	return (strlen(src));
}
