/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 00:42:04 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/11 01:02:46 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	substitute_spaces(char **user_input, int *i, char quote)
{
	while ((*user_input)[*i] && (*user_input)[*i] != quote)
	{
		if ((*user_input)[*i] == ' ')
			(*user_input)[*i] = (char)1;
		(*i)++;
	}
	if ((*user_input)[*i] != quote)
	{
		ft_printf("minishell: syntax error: quotes `%c' was expected to close\n", quote); //ou bash: ?
		return (0);
	}
	return (1);
}

int	handle_quotes_and_spaces(t_data *data)
{
	int	i;

	i = 0;
	while (data->user_input[i])
	{
		if (data->user_input[i] == '"')
		{
			i++;
			if (substitute_spaces(&data->user_input, &i, '"') == 0)
				return (0);
		}
		if (data->user_input[i] == '\'')
		{
			i++;
			if (substitute_spaces(&data->user_input, &i, '\'') == 0)
				return (0);
		}
		i++;
	}
	return (1);
}
