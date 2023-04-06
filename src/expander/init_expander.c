/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/01 03:34:55 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_expander(t_data *data)
{
	t_token	*aux_token;
	char	*new_content;
	char	*aux_trim;

	aux_token = data->tokens;
	while (aux_token)
	{
		separe_quotes(data, &aux_token->content);
		//arrumar $oi$oi e $oi"teste" e $oi'teste' etc --reutilizar funções
		aux_token = aux_token->next;
	}
}
