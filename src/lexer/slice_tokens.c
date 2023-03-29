/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:45:29 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/29 17:47:54 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	slice_tokens(t_data *data)
{
	(void)data;
}

// lexer(char *input, t_data *data)
// {
// while(input[i])
// {
// i += skip_blankspaces(&input[i], data);
// i += save_reserved_word(&input[i], data);
// i += save_word(&input[i], data);
// }
// }

// save_word(char *input)
// {
// Int i;

// i = 0
// while (input [i])
// {
// if (i == '\'' || i == '"')
// i +=save_quoted_word(&input[i]);
// else If (is_reserved(&input[i + 1]))
// break ;
// else
// i++;
// }
// add_token_2((&input[0]), i, data);
// return (i);
// }

//  add_token_2(char *word, int size, t_data *data)
// {
// char *new_word;

// new_word = ft_calloc(size + 1, sizeof(char));
// ft_strlcpy(new_word, word, size);
// token_push_back(&data->tokens, new_word);
// free (new_word);
// }
