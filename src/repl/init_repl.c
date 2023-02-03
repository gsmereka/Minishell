/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/03 14:14:18 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static bool	get_user_input(t_data *data);
static bool	is_valid(char *user_input);
static void	save_input_on_history(char *user_input);
static void	free_user_input(t_data *data);

void	init_repl(t_data *data)
{
	int	i;

	i = 0;
	data->prompt = "HopeShell:$ ";
	init_repl_signals_handling(data);
	while (1)
	{
		if (!get_user_input(data))
			break ;
		save_input_on_history(data->user_input);
		init_expander(data);
		init_lexer(data);
		init_parser(data);
		init_executor(data);
		free_user_input(data);
		i++;
	}
}

static void	save_input_on_history(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i] == '\t' || user_input[i] == ' ')
		i++;
	if (user_input[i] != '\0')
		add_history(user_input);
}

static bool	is_valid(char *user_input)
{
	if (!user_input)
	{
		ft_printf("exit\n");
		return (false);
	}
	else if (!ft_strncmp("exit", user_input, 4))
		return (false);
	return (true);
}

static bool	get_user_input(t_data *data)
{
	data->user_input = readline(data->prompt);
	if (!is_valid(data->user_input))
	{
		free_user_input(data);
		rl_clear_history();
		return (false);
	}
	return (true);
}

static void	free_user_input(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
}
