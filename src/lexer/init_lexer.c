/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/30 20:08:26 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	define_types(t_token *token);

void	init_lexer(t_data *data)
{
	slice_tokens(data);
	define_types(data->tokens);
}

static void	define_types(t_token *token)
{
	while (token)
	{
		if (ft_strcmp("|", token->content) == 0)
			token->type = ft_strdup("pipe");
		if (ft_strcmp("<", token->content) == 0)
			token->type = ft_strdup("redirect");
		if (ft_strcmp("<<", token->content) == 0)
			token->type = ft_strdup("redirect");
		if (ft_strcmp(">>", token->content) == 0)
			token->type = ft_strdup("redirect");
		if (ft_strcmp(">", token->content) == 0)
			token->type = ft_strdup("redirect");
		token = token->next;
	}
}
