/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/09 20:55:15 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_new_tokens(t_data *data, t_token *new_token)
{
	t_token	*aux_new;

	token_clear(&data->tokens);
	aux_new = new_token;
	while (aux_new)
	{
		add_token(&data->tokens, aux_new->content);
		if (aux_new->type)
			token_last(data->tokens)->type = ft_strdup(aux_new->type);
		aux_new = aux_new->next;
	}
	token_clear(&new_token);
}

void	init_expander(t_data *data)
{
	t_token	*aux_token;
	t_token	*new_token;

	aux_token = data->tokens;
	new_token = NULL;
	while (aux_token)
	{
		separe_quotes(data, &aux_token->content);
		if (ft_strlen(aux_token->content) > 0)
		{
			//criar o remove_$ antes de adicionar o content no novo token --só apaga o $ se n tiver nd dps
			add_token(&new_token, aux_token->content);
			if (aux_token->type)
				token_last(new_token)->type = ft_strdup(aux_token->type);
		}
		aux_token = aux_token->next;
	}
	set_new_tokens(data, new_token);
}
