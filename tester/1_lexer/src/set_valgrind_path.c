/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_valgrind_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:18:39 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 19:00:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static char	*test_path(t_data *data);
static void	set_pathfinder(char *envp[], t_data *data);
static char	*path_finder(char *envp[]);
static int	ft_addstr(char **s1, char *s2);

void	set_valgrind_path(t_data *data)
{
	set_pathfinder(data->envp, data);
	data->valgrind_path = test_path(data);
	if (!data->valgrind_path)
		exit_error(12, "Fail at find valgrind path\n", data);
}

static char	*test_path(t_data *data)
{
	char	*final_path;
	int		i;

	i = 0;
	while (data->paths[i])
	{
		final_path = strdup(data->paths[i]);
		ft_addstr(&final_path, "/");
		ft_addstr(&final_path, "valgrind");
		if (!final_path)
			exit_error(12,
				"Failed to allocate memory for test a command path\n", data);
		if (access(final_path, X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}

static void	set_pathfinder(char *envp[], t_data *data)
{
	char	*path_list;

	path_list = path_finder(envp);
	data->paths = ft_split(path_list, ':');
	if (!data->paths)
		exit_error(2, "Environment pointer have not a PATH\n", data);
}

static char	*path_finder(char *envp[])
{
	int	i;

	i = 0;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (strncmp("PATH=", envp[i], 5) == 0)
			break ;
		i++;
	}
	return (envp[i] + 5);
}

static int	ft_addstr(char **s1, char *s2)
{
	char	*new_s;
	int		s1_size;
	int		s2_size;
	int		i;

	if (*s1 == NULL)
		*s1 = strdup("");
	if (*s1 == NULL || !s2)
		return (-1);
	s1_size = strlen(*s1);
	s2_size = strlen(s2);
	new_s = (char *)calloc((s1_size + s2_size + 1), sizeof(char));
	if (new_s == NULL)
		return (-1);
	i = -1;
	while (++i < (s1_size + s2_size + 1))
	{
		if (i < s1_size)
			new_s[i] = (*s1)[i];
		else
			new_s[i] = s2[i - s1_size];
	}
	free(*s1);
	*s1 = new_s;
	return (0);
}
