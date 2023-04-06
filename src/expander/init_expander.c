/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/06 21:06:47 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_expander(t_data *data)
{
	t_token	*aux_token;
	char	*new_content;
	char	*aux_trim;
	t_token	*new_token;
	t_token	*aux_new;

	aux_token = data->tokens;
	new_token = NULL;
	while (aux_token)
	{
		separe_quotes(data, &aux_token->content);
		if (ft_strlen(aux_token->content) > 0)
			add_token(&new_token, aux_token->content);
		//arrumar $oi$oi e $oi"teste" e $oi'teste' etc --reutilizar funções
		aux_token = aux_token->next;
	}
	token_clear(&data->tokens);
	data->tokens = NULL;
	aux_new = new_token;
	while (aux_new)
	{
		add_token(&data->tokens, aux_new->content);
		aux_new = aux_new->next;
	}
	token_clear(&new_token);
	//delete_empty_tokens(data);
}
