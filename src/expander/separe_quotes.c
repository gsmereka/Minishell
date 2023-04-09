/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separe_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 02:32:10 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/08 02:57:49 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	separe_quotes(t_data *data, char **content)
{
	int		i;
	char	*str;
	char	*aux;
	char	*new_content;

	i = 0;
	str = NULL;
	new_content = NULL;
	aux = NULL;
	while ((*content)[i])
	{
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
			new_content = ft_strjoin_gnl(new_content, str);
			free(str);
			str = NULL;
		}
		if ((*content)[i] && (*content)[i] == '\"')
		{
			i++;
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
				new_content = ft_strjoin_gnl(new_content, str);
				free(str);
				str = NULL;
			}
		}
		if ((*content)[i] && (*content)[i] == '\'')
		{
			i++;
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
				new_content = ft_strjoin_gnl(new_content, str);
				free(str);
				str = NULL;
			}
		}
		if ((*content)[i])
			i++;
	}
	free(*content);
	if (new_content)
		*content = ft_strdup(new_content);
	else
		*content = ft_strdup("");
	free(new_content);

	/*		ler o content char por char   --- colocar isso fora da função em ingles? sim ( )
			armazena numa string se n for aspa dupla nem simples
			se for dupla, enquanto n achar outra dupla armazena numa string
			se for simples, enquanto n achar outra simples armazena numa string*/
}
