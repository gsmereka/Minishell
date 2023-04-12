/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/12 12:26:42 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void		att_envp_dictionary(char *save_pwd, t_data *data);
static int		validate_dir(char **dir, char *save_pwd, t_data *data);
static char		*get_pwd(int buffer_size, t_data *data);
static char		*set_home(char **dir, char *save_pwd, t_data *data);

void	ft_cd(char **args, t_data *data)
{
	int		dir_changed;
	char	*save_pwd;
	char	*path;

	if (args[1] && args[2])
	{
		ft_cd_error_msg(1, NULL, data);
		return ;
	}
	path = args[1];
	save_pwd = get_pwd(1024, data);
	if (!validate_dir(&path, save_pwd, data))
	{
		free (save_pwd);
		return ;
	}
	dir_changed = chdir(path);
	if (dir_changed != -1)
	{
		att_envp_dictionary(save_pwd, data);
		att_virtual_envp(data);
	}
	free (save_pwd);
}

static int	validate_dir(char **dir, char *save_pwd, t_data *data)
{
	struct stat	dir_info;

	if (!*dir || ft_strcmp(*dir, "~") == 0)
		*dir = set_home(dir, save_pwd, data);
	if (!*dir)
		return (0);
	dir_info = (struct stat){0};
	stat(*dir, &dir_info);
	if (access(*dir, F_OK) == -1)
		ft_cd_error_msg(5, *dir, data);
	else if (!S_ISDIR(dir_info.st_mode))
		ft_cd_error_msg(2, *dir, data);
	else if (access(*dir, X_OK) == -1)
		ft_cd_error_msg(3, *dir, data);
	else
		return (1);
	return (0);
}

static char	*set_home(char **dir, char *save_pwd, t_data *data)
{
	t_env	*home;

	home = find_env("HOME", data);
	if (!home || home->hidden_status != 0)
	{
		ft_cd_error_msg(4, NULL, data);
		return (NULL);
	}
	*dir = home->value;
	if (*dir[0] == '\0')
		*dir = save_pwd;
	return (*dir);
}

static char	*get_pwd(int buffer_size, t_data *data)
{
	char	*pwd;
	char	*error_msg;

	pwd = getcwd(NULL, buffer_size);
	if (!pwd)
	{
		if (buffer_size > 0)
			pwd = get_pwd(buffer_size * 2, data);
		else
		{
			error_msg = "path too long\n";
			write(2, error_msg, ft_strlen(error_msg));
			att_exit_status(1, data);
			return (NULL);
		}
	}
	return (pwd);
}

static void	att_envp_dictionary(char *save_pwd, t_data *data)
{
	static int	oldpwd_was_created_once;
	t_env		*oldpwd;
	t_env		*pwd;

	oldpwd = find_env("OLDPWD", data);
	pwd = find_env("PWD", data);
	if (pwd)
	{
		free(pwd->value);
		pwd->value = get_pwd(1024, data);
		pwd->hidden_status = 0;
	}
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(save_pwd);
		oldpwd->hidden_status = 0;
	}
}
