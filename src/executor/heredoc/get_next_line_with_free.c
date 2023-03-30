/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_with_free.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:16:23 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/22 16:52:50 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	*read_file(int fd, char *save)
{
	char	*buffer;
	int		len_read;

	buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	len_read = 1;
	while (len_read && !(ft_strchr_gnl(save, '\n')))
	{
		len_read = read(fd, buffer, BUFFER_SIZE);
		if (len_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[len_read] = '\0';
		save = ft_strjoin_gnl(save, buffer);
	}
	free(buffer);
	return (save);
}

static size_t	count_len_line(char *save)
{
	size_t	len_line;
	char	*aux_save;

	aux_save = save;
	len_line = 0;
	while (*aux_save && *aux_save != '\n')
	{
		len_line++;
		aux_save++;
	}
	return (len_line);
}

static char	*get_line(char *save)
{
	char	*line;
	size_t	len_line;

	if (!*save)
		return (NULL);
	len_line = count_len_line(save);
	line = malloc(sizeof(char *) * (len_line + 2));
	if (!line)
		return (NULL);
	len_line += 1;
	line[len_line] = '\0';
	while (len_line--)
		line[len_line] = save[len_line];
	return (line);
}

static char	*save_rest(char *save)
{
	char	*new_save;
	size_t	len_line;
	size_t	i;

	len_line = count_len_line(save);
	if (!save[len_line])
	{
		free(save);
		return (NULL);
	}
	new_save = malloc(ft_strlen_gnl(save) - len_line + 1);
	if (!new_save)
		return (NULL);
	len_line++;
	i = 0;
	while (save[len_line])
		new_save[i++] = save[len_line++];
	new_save[i] = '\0';
	free(save);
	return (new_save);
}

char	*get_next_line_with_free(int fd, int stop)
{
	static char	*save;
	char		*line;

	if (stop)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	save = read_file(fd, save);
	if (!save)
	{
		free (save);
		return (NULL);
	}
	line = get_line(save);
	save = save_rest(save);
	return (line);
}
