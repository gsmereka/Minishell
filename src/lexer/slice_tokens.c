/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 17:45:29 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/01 16:08:16 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_new_token(char *word, int size, t_data *data);
static int	save_normal_word(char *input, t_data *data);
static int	is_reserved_word(char *input);
static int	save_reserved_word(char *input, t_data *data);

void	slice_tokens(t_data *data)
{
	char	*input;
	int		i;

	i = 0;
	input = data->user_input;
	while (input[i])
	{
		while (input[i] == 32 || (input[i] >= 9 && input[i] <= 13))
			i++;
		i += save_reserved_word(&input[i], data);
		i += save_normal_word(&input[i], data);
	}
}

static int	save_reserved_word(char *input, t_data *data)
{
	int	skip;

	skip = is_reserved_word(input);
	set_new_token(input, skip, data);
	return (skip);
}

static int	save_normal_word(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input [i])
	{
		if (input[i] == '\'' && input[i + 1])
		{
			i++;
			while (input[i + 1] && input[i] != '\'' )
				i++;
		}
		else if (input[i] == '"' && input[i + 1])
		{
			i++;
			while (input[i + 1] && input[i] != '"')
				i++;
		}
		if (is_reserved_word(input + i)
			|| (input[i] == 32 || (input[i] >= 9 && input[i] <= 13)))
			break ;
		else
			i++;
	}
	set_new_token((&input[0]), i, data);
	return (i);
}

static int	is_reserved_word(char *input)
{
	if (ft_strncmp(input, "<<", 2) == 0)
		return (2);
	else if (ft_strncmp(input, "<", 1) == 0)
		return (1);
	else if (ft_strncmp(input, ">>", 2) == 0)
		return (2);
	else if (ft_strncmp(input, ">", 1) == 0)
		return (1);
	else if (ft_strncmp(input, "|", 1) == 0)
		return (1);
	return (0);
}

static void	set_new_token(char *word, int size, t_data *data)
{
	char	*new_word;

	if (!word || !*word || !size)
		return ;
	new_word = ft_calloc(size + 1, sizeof(char));
	if (!new_word)
		return ;
	ft_strlcpy(new_word, word, size + 1);
	add_token(&data->tokens, new_word);
	// ft_putstr_fd(new_word, 2);
	// ft_putchar_fd('\n', 2);
	free(new_word);
}
