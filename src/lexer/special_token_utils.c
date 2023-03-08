/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:49:54 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/08 01:51:40 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	add_special_tokens(t_data *data)
{
	t_token	*aux_token;
	int		i;

	aux_token = data->tokens;
	while (aux_token)
	{
		i = 0;
		while (aux_token->content[i])
		{
			if (aux_token->content[i] == '>' || aux_token->content[i] == '<' || \
				aux_token->content[i] == '|')
				//criar novos tokens
				i++;
			if (ft_strncmp(aux_token->content, ">>", 2) == 0 || \
				ft_strncmp(aux_token->content, "<<", 2) == 0)
				i += 2;
			i++;
		}
		
			aux_token->type = ft_strdup("redirect");
		ft_printf("%s\n", aux_token->type); //p teste
		aux_token = aux_token->next;
	}
}
