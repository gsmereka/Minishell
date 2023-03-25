/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 19:26:08 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/24 21:56:50 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	print_syntax_error_msg(char *token);
static int	search_errors(t_token *token);

// vou fazer um loop que vai salvando os heredocs, 
// o primeiro erro de syntax identificado é printado
// se tiver algum erro de syntax, os tokens são limpos, e é
// passada a lista com heredocs salvos
int	check_syntax(t_data *data)
{
	if (search_errors(data->tokens))
	{
		att_exit_status(2, data);
		return (1);
	}
	return (0);
}

static int	search_errors(t_token *token)
{
	while (token)
	{
		if (is_redirect(token))
		{
			if (!token->next)
				return (print_syntax_error_msg(""));
			if (is_reserved("<<", token->next))
				return (print_syntax_error_msg("<<"));
			if (is_reserved("<", token->next))
				return (print_syntax_error_msg("<"));
			if (is_reserved(">>", token->next))
				return (print_syntax_error_msg(">>"));
			if (is_reserved(">", token->next))
				return (print_syntax_error_msg(">"));
		}
		if (is_reserved("|", token))
		{
			if (!token->next)
				return (print_syntax_error_msg(""));
			if (is_reserved("|", token->next))
				return (print_syntax_error_msg("|"));
		}
		token = token->next;
	}
	return (0);
}

static int	print_syntax_error_msg(char *token)
{
	char	*msg;

	msg = "bash: syntax error near unexpected token `";
	if (!*token)
		token = "newline";
	msg = ft_strjoin(msg, token);
	msg = ft_strjoin_with_free(msg, "'\n");
	ft_putstr_fd(msg, 2);
	return (1);
}
