/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_quotes(t_data *g_data) //+ de 25 linhas
{
	int	i;

	i = 0;
	while (g_data->user_input[i])
	{
		if (g_data->user_input[i] == '"')
		{
			i++;
			while (g_data->user_input[i] && g_data->user_input[i] != '"')
			{
				if (g_data->user_input[i] == ' ')
					g_data->user_input[i] = (char)1;
				i++;
			}
		}
		if (g_data->user_input[i] == '\'')
		{
			i++;
			while (g_data->user_input[i] && g_data->user_input[i] != '\'')
			{
				if (g_data->user_input[i] == ' ')
					g_data->user_input[i] = (char)1;
				i++;
			}
		}
		i++; //
	}
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

void	init_lexer(t_data *g_data) //oq faz: separar a string por palavras   --- atenção nas aspas!   
{
	char	**user_input;
	int		i;

	handle_quotes(g_data);
	user_input = ft_split(g_data->user_input, ' ');
	user_input = set_spaces(user_input);
	i = 0;
	while (user_input[i])
	{
		add_token(&g_data->tokens, user_input[i]);
		i++;
	}
	free_mat_user_input(user_input);
}
