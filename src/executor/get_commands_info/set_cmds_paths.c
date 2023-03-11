/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds_paths.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:18:39 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/10 15:30:13 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static char	*test_path(int cmd, t_data *data);
static char	*ft_strjoin_with_free(char *s1, char *s2);

void	set_cmds_paths(t_data *data)
{
	int		cmd;
	char	*cmd_path;

	cmd = 0;
	while (cmd < data->exec->cmds_amount)
	{
		cmd_path = test_path(cmd, data);
		if (cmd_path != NULL)
		{
			free(data->exec->cmds[cmd]->name);
			data->exec->cmds[cmd]->name = cmd_path;
		}
		// ft_printf("caminho do programa: %s\n", data->exec->cmds[cmd]->name);
		cmd++;
	}
}

static char	*test_path(int cmd, t_data *data)
{
	char	*final_path;
	int		i;

	i = 0;
	if (!data->exec->cmds[cmd]->name)
		return (NULL);
	while (data->exec->env_paths[i])
	{
		final_path = ft_strdup(data->exec->env_paths[i]);
		final_path = ft_strjoin_with_free(final_path, "/");
		final_path = ft_strjoin_with_free
			(final_path, data->exec->cmds[cmd]->name);
		if (!final_path)
			exit_error(12,
				"Failed to allocate memory for test a command path", data);
		if (access(final_path, X_OK) == 0)
			return (final_path);
		free(final_path);
		i++;
	}
	return (NULL);
}

static char	*ft_strjoin_with_free(char *s1, char *s2)
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
