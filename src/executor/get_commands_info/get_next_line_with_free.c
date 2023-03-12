/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_with_free.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 02:24:40 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/12 12:50:23 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	*ft_read(int fd, char *next_s);
static char	*ft_actual_s(char *str);
static char	*ft_define_next_s(char *str);
static char	*ft_stradd(char *s1, char *s2);

char	*get_next_line_with_free(int fd, int stop)
{
	char		*actual_s;
	static char	*next_s;

	if (fd < 0)
		return (NULL);
	if (stop == 1)
	{
		free(next_s);
		return (NULL);
	}
	next_s = ft_read(fd, next_s);
	if (!next_s)
		return (NULL);
	actual_s = ft_actual_s(next_s);
	next_s = ft_define_next_s(next_s);
	return (actual_s);
}

static char	*ft_read(int fd, char *next_s)
{
	char	*temp_s;
	int		stop;

	temp_s = malloc(sizeof(char) * (2));
	if (!temp_s)
		return (NULL);
	stop = 1;
	while (stop != 0 && !ft_strchr(next_s, '\n'))
	{
		stop = read(fd, temp_s, 1);
		if (stop == -1)
		{
			free(temp_s);
			return (NULL);
		}
		temp_s[stop] = '\0';
		next_s = ft_stradd(next_s, temp_s);
	}
	free(temp_s);
	return (next_s);
}

static char	*ft_actual_s(char *s)
{
	char	*new_s;
	int		i;
	int		limit;

	if (!s || s[0] == '\0')
		return (NULL);
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		i++;
	new_s = malloc((i + 1) * sizeof(char));
	if (!new_s)
		return (NULL);
	limit = 0;
	while (limit < i)
	{
		new_s[limit] = s[limit];
		limit++;
	}
	new_s[i] = '\0';
	return (new_s);
}

static char	*ft_define_next_s(char *s)
{
	char	*new_s;
	int		n_pos;
	int		new_end;

	n_pos = 0;
	while (s[n_pos] != '\0' && s[n_pos] != '\n')
		n_pos++;
	if (s[n_pos] == '\0')
	{
		free(s);
		return (NULL);
	}
	n_pos++;
	new_s = (char *)malloc((1 + (ft_strlen(s) - n_pos)) * sizeof(char));
	if (new_s == NULL)
	{
		free(s);
		return (NULL);
	}
	new_end = 0;
	while (s[n_pos] != '\0')
		new_s[new_end++] = s[n_pos++];
	new_s[new_end] = '\0';
	free(s);
	return (new_s);
}

static char	*ft_stradd(char *s1, char *s2)
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
