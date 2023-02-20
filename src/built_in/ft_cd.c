/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:01:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/20 15:35:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	change_dir_at_dict_envp(char	*dir, t_data *data);
static int	dir_exist(char *dir);

void	ft_cd(char **args, t_data *data)
{
	char	*dir;
	int		dir_changed;

	if (!args || !args[1]) //verifica se tem argumentos
		return ;
	if (!dir_exist(args[1])) // verifica se o diretório existe
		return ;
	dir = ft_strdup(args[1]);
	if (!dir)
		exit_error(12, "Fail at alloc dir value at cd", data);
	dir_changed = chdir(dir); // tenta alterar o diretório atual
	if (dir_changed != -1) 
		change_dir_at_dict_envp(dir, data); // se alterou, altera a variavel de ambiente no dicionario.
	free(dir);
}

static void	change_dir_at_dict_envp(char	*dir, t_data *data)
{
	t_env	*pwd;

	pwd = data->dict_envp;
	while (pwd && ft_strncmp(pwd->key, "PWD", 4) != 0)
	{
		pwd = pwd->next;
	}
	if (pwd)
	{
		if (pwd->value)
			free(pwd->value);
		pwd->value = ft_strdup(dir);
		if (!pwd->value)
			exit_error(12, "Fail at alloc pwd value at cd", data);
	}
}

static int	dir_exist(char *dir)
{
	DIR	*path;

	path = opendir(dir);
	if (path)
	{
		closedir(path);
		return (1);
	}
	return (0);
}
