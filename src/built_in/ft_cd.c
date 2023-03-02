/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/02 11:43:52 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void		att_envp_dictionary(char *save_pwd, t_data *data);
static int		dir_exist(char *dir);
static char		*get_pwd(int buffer_size);
static int		buffer_size_overflow(int buffer_size);

void	ft_cd(char **args, t_data *data)
{
	int		dir_changed;
	char	*save_pwd;

	if (args[1] && args[2])
	{
		data->error_msg = "bash: cd: too many arguments";
		write(2, data->error_msg, ft_strlen(data->error_msg));
		data->exit_status = 1;
		return ;
	}
	if (!args[1])
		return ;
	if (!dir_exist(args[1])) // verifica se o diretório existe
		return ;
	save_pwd = get_pwd(1024);
	dir_changed = chdir(args[1]); // tenta alterar o diretório atual
	if (dir_changed != -1)
	{
		att_envp_dictionary(save_pwd, data);
		att_virtual_envp(data); // Tambem atualiza a virtual_envp
	}
	free(save_pwd);
}

static int	dir_exist(char *dir) //falta verificar permissões
{
	DIR	*path;

	path = opendir(dir); // tenta abrir o diretorio
	if (path) // se abrir, o diretório existe e tem acesso.
	{
		closedir(path);
		return (1);
	}
	return (0);
}

static char	*get_pwd(int buffer_size)
{
	char	*pwd;

	pwd = getcwd(NULL, buffer_size);
	if (!pwd)
	{
		if (!buffer_size_overflow(buffer_size))
			pwd = get_pwd(buffer_size * 2);
	}
	return (pwd);
}

static int	buffer_size_overflow(int buffer_size)
{
	if (buffer_size > 0)
		return (0);
	return (1);
}

static void	att_envp_dictionary(char *save_pwd, t_data *data)
{
	static int	first_time;
	t_env		*oldpwd;
	t_env		*pwd;

	oldpwd	= find_env("OLDPWD", data);
	pwd = find_env("PWD", data);
	if (pwd)
	{
		free(pwd->value);
		pwd->value = get_pwd(1024);
	}
	if (oldpwd)
	{
		free(oldpwd->value);
		oldpwd->value = ft_strdup(save_pwd);
	}
	if (first_time == 0)
	{
		if (!oldpwd)
			dict_add_back(&data->dict_envp, ft_strdup("OLDPWD"), ft_strdup(save_pwd));
		first_time++;
	}
}
