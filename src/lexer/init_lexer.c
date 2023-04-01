/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/31 21:14:45 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	define_types(t_token *token);
static int	is_closed_by(char quote, char *str);
static int	validate_tokens_quotes(t_token *token);
static void	print_error_msg(char *str, char quote);

void	init_lexer(t_data *data)
{
	slice_tokens(data);
	define_types(data->tokens);
	if (!validate_tokens_quotes(data->tokens))
	{
		att_exit_status(1, data);
		data->need_interrupt = 1;
	}
}

static int	validate_tokens_quotes(t_token *token)
{
	while (token && token->content)
	{
		if (!is_closed_by('\'', token->content))
		{
			print_error_msg(token->content, '\'');
			return (0);
		}
		if (!is_closed_by('"', token->content))
		{
			print_error_msg(token->content, '"');
			return (0);
		}
		token = token->next;
	}
	return (1);
}

static int	is_closed_by(char quote, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
		{
			i++;
			while (str[i] != quote)
			{
				if (!str[i])
					return (0);
				i++;
			}
		}
		i++;
	}
	return (1);
}

static void	print_error_msg(char *str, char quote)
{
	ft_putstr_fd("minishell: syntax error: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": was expected to be closed by `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("' \n", 2);
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
