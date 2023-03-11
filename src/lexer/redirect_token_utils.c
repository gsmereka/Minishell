/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_token_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 01:49:54 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/11 00:53:17 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*void	add_special_tokens(t_data *data)
{
	t_token	*aux_token;
	int		i;
	int		special;

	aux_token = data->tokens;
	while (aux_token)
	{
		i = 0;
		special = 0;
		while (aux_token->content[i])
		{
			if (aux_token->content[i] == '>' || aux_token->content[i] == '<' || \
				aux_token->content[i] == '|') || ft_strncmp(&aux_token->content[i], ">>", 2) == 0 || \
				ft_strncmp(&aux_token->content[i], "<<", 2) == 0) // e se len de content < 2?
				special = 1; //n sei se preciso fazer isso da flag na vdd
			i++;
		}
		if (special == 1)
			aux_token->type = ft_strdup("redirect"); //isso vai dar free dps q dividir em varios tokens, e só o q tiver os ngc vai ter esse type dnv
		aux_token = aux_token->next;
	} //dependendo do tamanho q o split der, vai ser a quantidade de tokens
		//mas como vai funcionar com varios desses ngc?
}
*/