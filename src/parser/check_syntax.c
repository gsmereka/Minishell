/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:26:08 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/24 21:00:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	search_errors(t_token *token, t_data *data);

// vou fazer um loop que vai salvando os heredocs, 
// o primeiro erro de syntax identificado é printado
// se tiver algum erro de syntax, os tokens são limpos, e é
// passada a lista com heredocs salvos
int	check_syntax(t_data *data)
{
	(void)data;
	search_errors(data->tokens, data);
	return (1);
}

static int	search_errors(t_token *token, t_data *data)
{
	while (token)
	{
		if (is_redirect(token, data))
		{
			if (token->next)
				(void)token;
		}
	}
	return (0);
}
