/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/03 12:31:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	init_loop(t_data *data);
static void	save_history(char *readline_buffer);
static bool	is_valid(char *readline_buffer);

void	init_repl(t_data *data)
{
	data->prompt = "HopeShell:$ ";
	data->readline_buffer = NULL;
	init_repl_signals(data);
	init_loop(data);
}

static void	init_loop(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		data->readline_buffer = readline(data->prompt);
		if (!is_valid(data->readline_buffer))
			break ;
		save_history(data->readline_buffer);
		if (data->readline_buffer)
			free(data->readline_buffer);
		i++;
	}
	rl_clear_history();
}

static void	save_history(char *readline_buffer)
{
	int	i;

	i = 0;
	while (readline_buffer[i] == '\t' || readline_buffer[i] == ' ')
		i++;
	if (readline_buffer[i] != '\0')
		add_history(readline_buffer);
}

static bool	is_valid(char *readline_buffer)
{
	if (!readline_buffer)
	{
		ft_printf("exit\n");
		return (false);
	}
	else if (!ft_strncmp("exit", readline_buffer, 4))
	{
		free(readline_buffer);
		return (false);
	}
	return (true);
}
