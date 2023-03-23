/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:54:21 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/23 11:09:54 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_pwd(int buffer_size);
static int	buffer_size_overflow(int buffer_size);

void	get_prompt(t_data *data)
{
	char	*path;

	if (data->prompt)
		free(data->prompt);
	path = get_pwd(1024);
	if (!path)
		return ;
	data->prompt = ft_strjoin("\033[1;32mHopeShell\033[0m:\033[1;34m~", path);
	free(path);
	data->prompt = ft_strjoin_with_free(data->prompt, "\033[0m$ ");
}

static char	*get_pwd(int buffer_size)
{
	char	*pwd;

	pwd = getcwd(NULL, buffer_size);
	if (!pwd)
	{
		if (!buffer_size_overflow(buffer_size))
			pwd = get_pwd(buffer_size * 2);
		else
			return (NULL);
	}
	return (pwd);
}

static int	buffer_size_overflow(int buffer_size)
{
	if (buffer_size > 0)
		return (0);
	return (1);
}
