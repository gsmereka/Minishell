/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/25 12:07:56 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	setup_repl(t_data *data);
static int	read_user_input(t_data *data);
static void	save_input_on_history(char *user_input, t_data *data);
static void	clear_repl(t_data *data);

void	init_repl(t_data *data)
{
	while (1)
	{
		setup_repl(data);
		if (!read_user_input(data))
			break ;
		init_lexer(data);
		init_expander(data);
		init_parser(data);
		init_executor(data);
		clear_repl(data);
	}
}

static void	setup_repl(t_data *data)
{
	set_prompt(data);
	init_repl_signals_handling(data);
}

static int	read_user_input(t_data *data)
{
	if (data->prompt)
		data->user_input = readline(data->prompt);
	else
		data->user_input = readline("\033[1;32mHopeShell\033[0m:$ ");
	if (!data->user_input)
	{
		ft_printf("exit\n");
		return (0);
	}
	save_input_on_history(data->user_input, data);
	return (1);
}

static void	save_input_on_history(char *user_input, t_data *data)
{
	int	i;

	i = 0;
	while (user_input[i] == '\t' || user_input[i] == ' ')
		i++;
	if (user_input[i] != '\0')
	{
		data->lines++;
		add_history(user_input);
	}
}

static void	clear_repl(t_data *data)
{
	if (data->error_msg)
		free(data->error_msg);
	clear_execution_data(data);
	token_clear(&data->tokens);
	free(data->user_input);
}
