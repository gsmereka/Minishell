/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:17:30 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/27 22:18:03 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tester.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_size;
	size_t	s2_size;
	char	*new_s;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_size = strlen(s1);
	s2_size = strlen(s2);
	new_s = (char *)calloc(s1_size + s2_size + 1, sizeof(char));
	while (i < (s1_size + s2_size + 1))
	{
		if (i >= s1_size)
			new_s[i] = s2[i - s1_size];
		else
			new_s[i] = s1[i];
		i++;
	}
	return ((char *)new_s);
}
