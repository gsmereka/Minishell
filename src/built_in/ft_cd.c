/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/01 01:03:17 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static t_env	*find_env(char *key, t_data *data);
static int		dir_exist(char *dir);
static char		*get_pwd(int buffer_size);
static int		buffer_size_overflow(int buffer_size);

void	ft_cd(char **args, t_data *data)
{
	int		dir_changed;
	char	*dir;

	if (args[1] && args[2])
	{
		data->error_msg = "bash: cd: too many arguments";
		write(2, data->error_msg, ft_strlen(data->error_msg));
		data->exit_status = 1;
		return ;
	}
	dir = args[1];
	if (!args[1] || (ft_strlen(args[1]) == 1 && args[1][0] == '~'))
	{
		dir = find_env("HOME", data)->value;
	}
	if (!dir_exist(dir)) // verifica se o diretório existe
		return ;
	dir_changed = chdir(dir); // tenta alterar o diretório atual
	if (dir_changed != -1)
	{
		if (find_env("OLDPWD", data))
		{
			free(find_env("OLDPWD", data)->value);
			find_env("OLDPWD", data)->value = find_env("PWD", data)->value;
		}
		if (find_env("PWD", data))
		{
			find_env("PWD", data)->value = get_pwd(1024);
			if (!find_env("PWD", data)->value)
				exit_error(12, "Fail at alloc envp value at cd", data);
		}
		att_virtual_envp(data); // Tambem atualiza a virtual_envp
	}
}

static t_env	*find_env(char *key, t_data *data)
{
	t_env	*envp;

	envp = data->dict_envp;
	while (envp) // busca a variavel de ambiente
	{
		if (ft_strncmp(envp->key, key, ft_strlen(key)) == 0)
			break ;
		envp = envp->next;
	}
	return (envp);
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
