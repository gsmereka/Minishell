/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:36:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/19 18:07:56 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	free_program_memory(t_data *data);

void	end_program(t_data *data)
{
	free_program_memory(data);
	exit(0);
}

void	exit_error(int error_value, char *msg, t_data *data)
{
	ft_printf(msg);
	free_program_memory(data);
	exit(error_value);
}

static void	free_program_memory(t_data *data)
{
	if (data->user_input)
		free(data->user_input);
	rl_clear_history();
}
