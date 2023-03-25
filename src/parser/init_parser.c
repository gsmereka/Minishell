/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/24 21:55:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	save_heredocs(t_data *data);
static void	swap_tokens_list(t_token *save, t_data *data);

void	init_parser(t_data *data)
{
	if (!data->tokens)
		return ;
	if (check_syntax(data))
		save_heredocs(data);
}

static void	save_heredocs(t_data *data)
{
	t_token	*token;
	t_token	*save;

	token = data->tokens;
	while (token)
	{
		if (is_reserved("<<", token))
		{
			if (token->next && !token->next->type)
			{
				add_token(&save, token->content);
				token->type = ft_strdup("redirect");
				add_token(&save, token->next->content);
			}
			else
				break ;
		}
		else if (is_reserved("|", token) && !token->next)
			break ;
		else if (is_reserved("|", token) && (is_reserved("|", token->next)))
			break ;
		token = token->next;
	}
	swap_tokens_list(save, data);
}

static void	swap_tokens_list(t_token *save, t_data *data)
{
	token_clear(&data->tokens);
	data->tokens = save;
}
