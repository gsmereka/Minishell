/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/01 18:23:48 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	define_types(t_token *token);
static int	is_closed(char *str);
static int	validate_tokens_quotes(t_token *token);
static int	print_error_msg(char *str, char quote);

void	init_lexer(t_data *data)
{
	slice_tokens(data);
	define_types(data->tokens);
	if (!data->tokens)
		return ;
	if (!validate_tokens_quotes(data->tokens))
	{
		att_exit_status(2, data);
		data->need_interrupt = 1;
	}
}

static int	validate_tokens_quotes(t_token *token)
{
	char	*str;

	str = token->content;
	while (token && token->content)
	{
		if (!is_closed(token->content))
			return (0);
		token = token->next;
	}
	return (1);
}

static int	is_closed(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'' )
			{
				if (!str[i])
					return (print_error_msg(str, '\''));
			}
		}
		if (str[i] == '"')
		{
			while (str[++i] != '"' )
			{
				if (!str[i])
					return (print_error_msg(str, '"'));
			}
		}
	}
	return (1);
}

static int	print_error_msg(char *str, char quote)
{
	ft_putstr_fd(">\n", 2);
	ft_putstr_fd("bash: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(quote, 2);
	ft_putstr_fd("' \n", 2);
	ft_putstr_fd("bash: syntax error: unexpected end of file\n", 2);
	return (0);
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
