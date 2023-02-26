/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   att_virtual_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:43:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/26 18:05:10 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	calculate_envp_size(t_data *data);
static void	fill_virtual_envp(t_data *data);
static char	*ft_strjoin_with_free(char *s1, char *s2);

void	att_virtual_envp(t_data *data)
{
	int		size;

	if (data->virtual_envp)
		free_array_list((void **)data->virtual_envp);
	size = calculate_envp_size(data);
	data->virtual_envp = ft_calloc(size + 1, sizeof(char *));
	if (!data->virtual_envp)
		exit_error(12, "Fail at alloc virtual envp memory", data);
	fill_virtual_envp(data);
}

static int	calculate_envp_size(t_data *data)
{
	t_env	*envp;
	int		size;

	size = 0;
	envp = data->dict_envp;
	while (envp)
	{
		size++;
		envp = envp->next;
	}
	return (size);
}

static void	fill_virtual_envp(t_data *data)
{
	t_env	*dict_envp;
	char	*key;
	int		i;

	i = 0;
	dict_envp = data->dict_envp;
	while (dict_envp)
	{
		key = ft_strdup(dict_envp->key);
		data->virtual_envp[i] = ft_strjoin_with_free(key, "=");
		data->virtual_envp[i]
			= ft_strjoin_with_free(data->virtual_envp[i], dict_envp->value);
		if (!data->virtual_envp[i])
			exit_error(12, "Fail at fill virtual envp memory", data);
		dict_envp = dict_envp->next;
		i++;
	}
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
