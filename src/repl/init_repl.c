/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/03 13:39:30 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	init_loop(t_data *data);
static void	save_history(char *user_input);
static bool	is_valid(char *user_input);

void	init_repl(t_data *data)
{
	data->prompt = "HopeShell:$ ";
	init_repl_signals(data);
	init_loop(data);
}

static void	init_loop(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		data->user_input = readline(data->prompt);
		if (!is_valid(data->user_input))
			break ;
		save_history(data->user_input);
		if (data->user_input)
			free(data->user_input);
		i++;
	}
	rl_clear_history();
}

static void	save_history(char *user_input)
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
	{
		free(user_input);
		return (false);
	}
	return (true);
}
