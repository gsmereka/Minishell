/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/10 00:59:11 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_new_tokens(t_data *data, t_token *new_token)
{
	t_token	*aux_new;

	token_clear(&data->tokens);
	aux_new = new_token;
	while (aux_new)
	{
		add_token(&data->tokens, aux_new->content);
		if (aux_new->type)
			token_last(data->tokens)->type = ft_strdup(aux_new->type);
		aux_new = aux_new->next;
	}
	token_clear(&new_token);
}

static int	verify_char(char **content, int i, int simpl_quote, int doubl_quote)
{
	if ((*content)[i] == '$' && !(*content)[i + 1])
		return (1);
	else if ((*content)[i] != '$')
		return (1);
	else if (((*content)[i + 1] != '"' || doubl_quote != 0) \
		&& ((*content)[i + 1] != '\'' || simpl_quote != 0))
		return (1);
	else if ((*content)[i + 1] == '$')
		return (1);
	return (0);
}

static void	remove_env_char(char **content)
{
	char	*new_content;
	int		i;
	char	*aux;
	int		simple_quote;
	int		double_quote;

	new_content = NULL;
	aux = NULL;
	simple_quote = 0;
	double_quote = 0;
	i = -1;
	while ((*content)[++i])
	{
		if ((*content)[i] == '\'')
		{
			if (simple_quote == 0)
				simple_quote = 1;
			else
				simple_quote = 0;
		}
		else if ((*content)[i] == '\"') //else if?
		{
			if (double_quote == 0)
				double_quote = 1;
			else
				double_quote = 0;
		}
		if (verify_char(content, i, simple_quote, double_quote))
		{
			aux = malloc(2);
			aux[0] = (*content)[i];
			aux[1] = '\0';
			new_content = ft_strjoin_gnl(new_content, aux);
			free(aux);
			aux = NULL;
		}
	}
	free(*content);
	*content = ft_strdup(new_content);
	free(new_content);
}

void	init_expander(t_data *data)
{
	t_token	*aux_token;
	t_token	*new_token;

	aux_token = data->tokens;
	new_token = NULL;
	while (aux_token)
	{
		remove_env_char(&aux_token->content);
		separe_quotes(data, &aux_token->content);
		if (ft_strlen(aux_token->content) > 0)
		{
			add_token(&new_token, aux_token->content);
			if (aux_token->type)
				token_last(new_token)->type = ft_strdup(aux_token->type);
		}
		aux_token = aux_token->next;
	}
	set_new_tokens(data, new_token);
}
