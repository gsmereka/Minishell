/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 04:17:35 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/02 15:10:51 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_token	*create_token(char *content);
void	add_token(t_token **tokens, char *content);
void	token_clear(t_token **tokens);

t_token	*create_token(char *content)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->type = NULL;
	new_node->content = ft_strdup(content);
	new_node->next = NULL;
	return (new_node);
}

t_token	*token_last(t_token *token)
{
	t_token	*last_token;

	last_token = token;
	if (!token)
		return (token);
	while (last_token->next)
		last_token = last_token->next;
	return (last_token);
}

void	add_token(t_token **tokens, char *content)
{
	t_token	*last_node;
	t_token	*new_node;

	if (!*tokens)
		*tokens = create_token(content);
	else
	{
		last_node = token_last(*tokens);
		new_node = create_token(content);
		last_node->next = new_node;
	}
}

void	token_clear(t_token **tokens)
{
	if (*tokens)
	{
		token_clear(&(*tokens)->next);
		free((*tokens)->content);
		free((*tokens)->type);
		free(*tokens);
		*tokens = NULL;
	}
}
