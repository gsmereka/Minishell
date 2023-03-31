/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_with_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:29:57 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 21:38:20 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	*ft_strjoin_with_free(char *s1, char *s2)
{
	char	*new_s;
	int		s1_size;
	int		s2_size;
	int		i;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 | !s2)
		return (NULL);
	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	new_s = (char *)malloc((s1_size + s2_size + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	while (i < (s1_size + s2_size + 1))
	{
		if (i < s1_size)
			new_s[i] = s1[i];
		else
			new_s[i] = s2[i - s1_size];
		i++;
	}
	free(s1);
	return ((char *)new_s);
}
