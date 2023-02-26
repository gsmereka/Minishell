/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:36:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/26 15:30:59 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	free_data(t_data *data);

// Saida normal do minishell, atraves do ctrl + D ou do comando exit.
void	end_program(t_data *data)
{
	int	exit_status;

	exit_status = data->exit_status;
	free_data(data);
	exit(exit_status);
}

// Saída pra quando houver algum erro interno,
// como falha na alocação de memorioa e etc...
void	exit_error(int error_value, char *msg, t_data *data)
{
	ft_printf("%s\n", msg);
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
