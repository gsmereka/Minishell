/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:45:29 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/29 17:58:12 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_new_token(char *word, int size, t_data *data);
static int	save_word(char *input, t_data *data);

void	slice_tokens(t_data *data)
{
	char	*input;
	int		i;

	i = 0;
	input = data->user_input;
	while (input[i])
	{
		// i += skip_blankspaces(&input[i], data);
		// i += save_reserved_word(&input[i], data);
		i += save_word(&input[i], data);
	}
}

static int	save_word(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input [i])
	{
		// if (input[i] == '\'' || input[i] == '"')
		// 	i += save_quoted_word(&input[i]);
		// else if (is_reserved(&input[i + 1]))
		// 	break ;
		// else
			i++;
	}
	set_new_token((&input[0]), i, data);
	return (i);
}

static void	set_new_token(char *word, int size, t_data *data)
{
	char	*new_word;

	new_word = ft_calloc(size + 1, sizeof(char));
	ft_strlcpy(new_word, word, size + 1);
	add_token(&data->tokens, new_word);
}
