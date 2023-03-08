/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/08 03:26:19 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	substitute_spaces_and_check_closed(t_data *data, char quote, int i)
{
	while (data->user_input[++i] && data->user_input[i] != quote)
	{
		if (data->user_input[i] == ' ')
			data->user_input[i] = (char)1;
	}
	if (data->user_input[i] != quote)
	{
		ft_printf("minishell: syntax error: quotes `%c' was expected to close\n", quote); //ou bash: ?
		return (0);
	}
	return (i);
}

static int	handle_quotes(t_data *data) // + de 25 linhas
{
	int	i;
	int	position;

	i = -1;
	while (data->user_input[++i])
	{
		position = 0; //isso é aq ou antes do while? --acho q aq pq é um auxiliar...?
		if (data->user_input[i] == '"')
		{
			position = substitute_spaces_and_check_closed(data, '"', i);
			if (!position)
				return (0);
			i += position;
			
		}
		if (data->user_input[i] == '\'')
		{
			position = substitute_spaces_and_check_closed(data, '\'', i);
			if (!position)
				return (0);
			i += position;
		}
	}
	return (1);
}

char	**set_spaces(char **user_input)
{
	int	i;
	int j;

	if (user_input == NULL)
		return (NULL);
	i = 0;
	while (user_input[i])
	{
		j = 0;
		while (user_input[i][j])
		{
			if (user_input[i][j] == (char)1)
				user_input[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (user_input);
}

void	free_mat_user_input(char **user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		free(user_input[i]);
		i++;
	}
	free(user_input);
	user_input = NULL;
}

int	init_lexer(t_data *data) //oq faz: separar a string por palavras   --- atenção nas aspas!   
{
	char	**user_input;
	int		i;

	if (!handle_quotes(data))
		return (0);
	user_input = ft_split(data->user_input, ' ');
	user_input = set_spaces(user_input);
	i = 0;
	while (user_input[i])
	{
		add_token(&data->tokens, user_input[i]);
		i++;
	}
	free_mat_user_input(user_input);
//	add_special_tokens(data);
	return (1);
}
