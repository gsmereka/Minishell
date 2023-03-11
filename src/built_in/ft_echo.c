/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:39 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/05 01:33:09 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	identify_flags(int *n_flag, char **args);
static void	display_text_line(int *n_flag, t_data *data);

// Se o primeiro argumento for -n, ele retira a quebra de linha no final.
void	ft_echo(char **args, t_data *data)
{
	int	n_flag;

	n_flag = 0;
	if (!args || !args[1])
		return ;
	identify_flags(&n_flag, args);
	display_text_line(&n_flag, data);
}

static void	identify_flags(int *n_flag, char **args)
{
	if (ft_strncmp(args[1], "-n", 2) == 0)
		*n_flag = 1;
}

static void	display_text_line(int *n_flag, t_data *data)
{
	int		i;
	t_token	*aux_token;

	i = 1;
	aux_token = data->tokens->next;
	if (*n_flag)
		i++;
	while (aux_token)
	{
		write(1, aux_token->content, ft_strlen(aux_token->content));
		if (aux_token->next)							 // se ainda não for a ultima palavra
			write(1, " ", 1);
		aux_token = aux_token->next;
	}
	if (*n_flag == 0) 						// se o primeiro argumento for -n
		write(1, "\n", 1);
}
