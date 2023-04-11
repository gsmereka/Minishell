/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/11 14:50:05 by gsmereka         ###   ########.fr       */
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
	if (!data->tokens)
		att_exit_status(0, data);
}

static int	verify_char(char **content, int i, t_expand_aux *expand_aux)
{
	if ((*content)[i] == '$' && !(*content)[i + 1])
		return (1);
	else if ((*content)[i] != '$')
		return (1);
	else if (((*content)[i + 1] != '"' || expand_aux->double_quote != 0) \
		&& ((*content)[i + 1] != '\'' || expand_aux->simple_quote != 0))
		return (1);
	else if ((*content)[i + 1] == '$')
		return (1);
	return (0);
}

static void	check_quote(char **content, int i, t_expand_aux *expand_aux)
{
	if ((*content)[i] == '\'')
	{
		if (expand_aux->simple_quote == 0)
			expand_aux->simple_quote = 1;
		else
			expand_aux->simple_quote = 0;
	}
	else if ((*content)[i] == '\"')
	{
		if (expand_aux->double_quote == 0)
			expand_aux->double_quote = 1;
		else
			expand_aux->double_quote = 0;
	}
}

static void	remove_env_char(char **content)
{
	t_expand_aux	expand_aux;
	int				i;

	ft_bzero(&expand_aux, sizeof(t_expand_aux));
	i = -1;
	while ((*content)[++i])
	{
		check_quote(content, i, &expand_aux);
		if (verify_char(content, i, &expand_aux))
		{
			expand_aux.aux = malloc(2);
			expand_aux.aux[0] = (*content)[i];
			expand_aux.aux[1] = '\0';
			expand_aux.new_content = ft_strjoin_gnl(expand_aux.new_content, \
				expand_aux.aux);
			free(expand_aux.aux);
			expand_aux.aux = NULL;
		}
	}
	free(*content);
	*content = ft_strdup(expand_aux.new_content);
	free(expand_aux.new_content);
	expand_aux.new_content = NULL;
}

void	init_expander(t_data *data)
{
	t_token	*aux_token;
	t_token	*new_token;
	int		null_flag;

	if (!data->tokens || data->need_interrupt)
		return ;
	aux_token = data->tokens;
	new_token = NULL;
	while (aux_token)
	{
		null_flag = 0;
		if (is_null_cmd(aux_token->content))
			null_flag = 1;
		remove_env_char(&aux_token->content);
		separe_quotes(data, &aux_token->content);
		if (ft_strlen(aux_token->content) > 0 || null_flag == 1)
		{
			add_token(&new_token, aux_token->content);
			if (aux_token->type)
				token_last(new_token)->type = ft_strdup(aux_token->type);
		}
		aux_token = aux_token->next;
	}
	set_new_tokens(data, new_token);
}
