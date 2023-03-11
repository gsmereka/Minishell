/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 01:05:13 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/11 05:44:57 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	check_envp_position_in_token(char **content)
{
	char	**mat_content;
	int		i;
	char	**mat_token;

	if (!*content)
		return ;
	mat_content = ft_split(*content, '$');
	if (!mat_content || !*mat_content) //assim?
		return ;
	mat_token = NULL;
	i = 0;
	if (mat_len(mat_content) > 1) // ft_strlen ** e *... warning
	{
		mat_token = (char **)malloc(sizeof(char *) * (mat_len(mat_content) + 1)); //colocar verificação aqui?
		mat_token[i] = ft_strdup(mat_content[i]);
		i++;
		while (mat_content[i])
		{
			mat_token[i] = ft_strdup("$");
			mat_token[i] = ft_strjoin_gnl(mat_token[i], mat_content[i]);
			i++;
		}
		mat_token[i] = NULL;

		//print p teste
		i = 0;
		while (mat_token[i])
		{
			ft_printf("%s\n", mat_token[i]);
			i++;
		}
		//
		free_mat(mat_token);
	}
	free_mat(mat_content);
}
