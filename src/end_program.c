/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:36:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/19 17:49:18 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	free_program_memory(t_data);

void	end_program(t_data *data)
{
	free_program_memory(data);
	(void)data;
}

void	exit_Error(t_data *data)
{
	free_program_memory(data);
	(void)data;
}

static void	free_program_memory(t_data)
{
	if (data->user_input)
		free(data->user_input);
	rl_clear_history();
}
