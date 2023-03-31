/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:26:08 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/30 21:43:45 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	print_syntax_error_msg(char *token, t_data *data);
static int	search_errors(t_token *token, t_data *data);

int	check_syntax(t_data *data)
{
	if (search_errors(data->tokens, data))
	{
		att_exit_status(2, data);
		return (1);
	}
	return (0);
}

static int	search_errors(t_token *token, t_data *data)
{
	if (is_reserved("|", token))
		return (print_syntax_error_msg("|", data));
	while (token)
	{
		if (is_reserved("|", token) || is_redirect(token))
		{
			if (!token->next)
				return (print_syntax_error_msg("", data));
			if (is_reserved("|", token->next))
				return (print_syntax_error_msg("|", data));
		}
		if (is_redirect(token))
		{
			if (is_reserved("<<", token->next))
				return (print_syntax_error_msg("<<", data));
			if (is_reserved("<", token->next))
				return (print_syntax_error_msg("<", data));
			if (is_reserved(">>", token->next))
				return (print_syntax_error_msg(">>", data));
			if (is_reserved(">", token->next))
				return (print_syntax_error_msg(">", data));
		}
		token = token->next;
	}
	return (0);
}

static int	print_syntax_error_msg(char *token, t_data *data)
{
	char	*msg;

	msg = "bash: syntax error near unexpected token `";
	if (!*token)
	{
		data->error_msg
			= ft_strdup("bash: syntax error near unexpected token `newline'\n");
		return (1);
	}
	msg = ft_strjoin(msg, token);
	msg = ft_strjoin_with_free(msg, "'\n");
	ft_putstr_fd(msg, 2);
	free(msg);
	return (1);
}
