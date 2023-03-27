/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/27 07:32:28 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	**set_spaces(char **user_input)
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

static void	free_mat_user_input(char **user_input)
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

	if (!handle_quotes_and_spaces(data))
		return (0);
	user_input = ft_split(data->user_input, ' ');
	user_input = set_spaces(user_input);
	i = 0;
	while (user_input[i])
	{
		add_token(&data->tokens, user_input[i]);
		i++;
	}
	free_mat_user_input(user_input); //
//	check_redirect_tokens(data);
//	create_new_tokens(data);
	return (1);
}
