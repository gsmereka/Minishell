/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/25 12:12:25 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void		save_heredocs(t_data *data);
static void		swap_tokens_list(t_token *save, t_data *data);
static t_token	*create_saved_token(char *content, char *type);
static void		add_saved_token(t_token **tokens, char *content, char *type);

void	define_types(t_token *token)
{
	while (token)
	{
		if (ft_strcmp("|", token->content) == 0)
			token->type = ft_strdup("isso ai");
		if (ft_strcmp("<", token->content) == 0)
			token->type = ft_strdup("isso ai");
		if (ft_strcmp("<<", token->content) == 0)
			token->type = ft_strdup("isso ai");
		if (ft_strcmp(">>", token->content) == 0)
			token->type = ft_strdup("isso ai");
		if (ft_strcmp(">", token->content) == 0)
			token->type = ft_strdup("isso ai");
		token = token->next;
	}
}

void	init_parser(t_data *data)
{
	if (!data->tokens)
		return ;
	define_types(data->tokens); /// somente pra testes
	if (check_syntax(data))
		save_heredocs(data);
}

static void	save_heredocs(t_data *data)
{
	t_token	*token;
	t_token	*save;

	save = NULL;
	token = data->tokens;
	while (token)
	{
		if (is_reserved("<<", token))
		{
			if (token->next && !token->next->type)
			{
				add_saved_token(&save, token->content, "redirect");
				add_saved_token(&save, token->next->content, NULL);
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

static t_token	*create_saved_token(char *content, char *type)
{
	t_token	*new_node;

	new_node = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new_node)
		return (NULL);
	if (type)
		new_node->type = ft_strdup(type);
	new_node->content = ft_strdup(content);
	return (new_node);
}

void	add_saved_token(t_token **tokens, char *content, char *type)
{
	t_token	*last_node;
	t_token	*new_node;

	if (!*tokens)
		*tokens = create_saved_token(content, type);
	else
	{
		last_node = token_last(*tokens);
		new_node = create_saved_token(content, type);
		last_node->next = new_node;
	}
}
