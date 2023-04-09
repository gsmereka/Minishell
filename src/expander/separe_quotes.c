/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separe_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:32:10 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/09 21:51:59 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	double_quoted(t_data *data, char **content, int i, char **new)
{
	char	*str;
	char	*aux;

	i++;
	str = NULL;
	aux = NULL;
	while ((*content)[i] && (*content)[i] != '\"')
	{
		aux = malloc(2);
		aux[0] = (*content)[i];
		aux[1] = '\0';
		str = ft_strjoin_gnl(str, aux);
		free(aux);
		i++;
	}
	if (str)
	{
		check_envp_position(data, &str);
		*new = ft_strjoin_gnl(*new, str);
		free(str);
		str = NULL;
	}
	return (i);
}

static int	simple_quoted(t_data *data, char **content, int i, char **new)
{
	char	*str;
	char	*aux;

	i++;
	str = NULL;
	aux = NULL;
	while ((*content)[i] && (*content)[i] != '\'')
	{
		aux = malloc(2);
		aux[0] = (*content)[i];
		aux[1] = '\0';
		str = ft_strjoin_gnl(str, aux);
		free(aux);
		i++;
	}
	if (str)
	{
		*new = ft_strjoin_gnl(*new, str);
		free(str);
		str = NULL;
	}
	return (i);
}

static int	unquoted(t_data *data, char **content, int i, char **new)
{
	char	*str;
	char	*aux;

	str = NULL;
	aux = NULL;
	while ((*content)[i] && (*content)[i] != '\"' && (*content)[i] != '\'')
	{
		aux = malloc(2);
		aux[0] = (*content)[i];
		aux[1] = '\0';
		str = ft_strjoin_gnl(str, aux);
		free(aux);
		i++;
	}
	if (str)
	{
		check_envp_position(data, &str);
		*new = ft_strjoin_gnl(*new, str);
		free(str);
		str = NULL;
	}
	return (i);
}

void	separe_quotes(t_data *data, char **content)
{
	int		i;
	char	*new_content;

	i = 0;
	new_content = NULL;
	while ((*content)[i])
	{
		i = unquoted(data, content, i, &new_content);
		if ((*content)[i] && (*content)[i] == '\"')
			i = double_quoted(data, content, i, &new_content);
		if ((*content)[i] && (*content)[i] == '\'')
			i = simple_quoted(data, content, i, &new_content);
		if ((*content)[i])
			i++;
	}
	free(*content);
	if (new_content)
	{
		*content = ft_strdup(new_content);
		free(new_content);
	}
	else
		*content = ft_strdup("");
}
