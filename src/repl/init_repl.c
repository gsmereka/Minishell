/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/19 12:17:07 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	get_user_input(t_data *data);
static int	is_valid(char *user_input);
static void	save_input_on_history(char *user_input);

void	init_repl(t_data *data)
{
	data->prompt = "HopeShell:$ ";
	while (1)
	{
		init_repl_signals_handling(data);
		get_user_input(data);
		if (!is_valid(data->user_input))
			break ;
		save_input_on_history(data->user_input);
		init_lexer(data);
		init_expander(data); //se o usuário mandou alguma var de ambiente  --- $
		// init_parser(data);
		init_executor(data);
		clear_commands(data);
		token_clear(&data->tokens); //p teste --isso vem dps --talvez no end_program e exit_error
		free(data->user_input);
	}
}

static void	save_input_on_history(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i] == '\t' || user_input[i] == ' ')
		i++;
	if (user_input[i] != '\0')
		add_history(user_input); //p n salvar historico vazio
}

static int	is_valid(char *user_input)
{
	if (!user_input)
	{
		ft_printf("exit\n"); //ele deve printar exit?
		return (0);
	}
	return (1);
}

static void	get_user_input(t_data *data)
{
	data->user_input = readline(data->prompt);
}
