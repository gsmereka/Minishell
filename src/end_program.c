/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:36:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/26 15:14:54 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	free_data(t_data *data);

void	end_program(t_data *data)
{
	free_data(data);
	exit(0);
}

void	exit_error(int error_value, char *msg, t_data *data)
{
	ft_printf(msg);
	free_data(data);
	exit(error_value);
}

static void	free_data(t_data *data)
{
	if (data->dict_envp)
		dictclear(data->dict_envp);
	if (data->user_input)
		free(data->user_input);
	rl_clear_history();
}
