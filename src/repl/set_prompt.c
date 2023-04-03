/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 00:54:21 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/02 21:41:33 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	*get_pwd(int buffer_size);
static int	buffer_size_overflow(int buffer_size);
static char	*check_if_is_home(char *pwd, t_data *data);

void	set_prompt(t_data *data)
{
	char	*path;
	char	*green_color;
	char	*blue_color;
	char	*white_color;

	green_color = ft_strdup("\001\033[1;32m\002");
	blue_color = ft_strdup("\001\033[1;34m\002");
	white_color = ft_strdup("\001\033[0m\002");
	if (data->prompt)
		free(data->prompt);
	path = get_pwd(1024);
	path = check_if_is_home(path, data);
	data->prompt = ft_strjoin(green_color, "HopeShell");
	data->prompt = ft_strjoin_with_free(data->prompt, white_color);
	data->prompt = ft_strjoin_with_free(data->prompt, ":");
	data->prompt = ft_strjoin_with_free(data->prompt, blue_color);
	data->prompt = ft_strjoin_with_free(data->prompt, "~");
	data->prompt = ft_strjoin_with_free(data->prompt, path);
	data->prompt = ft_strjoin_with_free(data->prompt, white_color);
	data->prompt = ft_strjoin_with_free(data->prompt, "$ ");
	free(green_color);
	free(blue_color);
	free(white_color);
	free(path);
}

static char	*check_if_is_home(char *pwd, t_data *data)
{
	t_env	*home_env;
	char	*save;
	int		i;

	home_env = find_env("HOME", data);
	if (!home_env || !home_env->value || !pwd)
		return (pwd);
	if (ft_strcmp(pwd, home_env->value) == 0)
	{
		free (pwd);
		return (ft_strdup(""));
	}
	i = 0;
	while (home_env->value[i] == pwd[i])
		i++;
	if (!home_env->value[i] && pwd[i])
	{
		save = ft_strdup(pwd + i);
		free (pwd);
		return (save);
	}
	return (pwd);
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
