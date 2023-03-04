/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/04 23:15:38 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	handle_quotes(t_data *data) //+ de 25 linhas
{
	int	i;

	i = 0;
	while (data->user_input[i])
	{
		if (data->user_input[i] == '"')
		{
			i++;
			while (data->user_input[i] && data->user_input[i] != '"')
			{
				if (data->user_input[i] == ' ')
					data->user_input[i] = (char)1;
				i++;
			}
		}
		if (data->user_input[i] == '\'')
		{
			i++;
			while (data->user_input[i] && data->user_input[i] != '\'')
			{
				if (data->user_input[i] == ' ')
					data->user_input[i] = (char)1;
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

void	init_lexer(t_data *data) //oq faz: separar a string por palavras   --- atenção nas aspas!   
{
	char	**user_input;
	int		i;

	handle_quotes(data);
	user_input = ft_split(data->user_input, ' ');
	user_input = set_spaces(user_input);
	i = 0;
	while (user_input[i])
	{
		add_token(&data->tokens, user_input[i]);
		i++;
	}
	free_mat_user_input(user_input);
	
	//p printar --teste
/*	t_token *aux_print;
	aux_print = data->tokens;
	while (aux_print)
	{
		ft_printf("%s\n", aux_print->content);
		aux_print = aux_print->next;
	}*/
	//ver expansor dps -- fazer lexer basico antes
	//expansor em mais tokens ($) ---isso vem antes do lexer   ---identifica se tem env na entrada, transforma em tokens no expansor e dps vem pra cá? ou expansor é chamado dentro do lexer? acho q expansor chama o lexer dps de pegar oq é a var de ambiente -> e transforma em token
	//vars de ambiente?
}
