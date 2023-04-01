/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:30:54 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/01 19:33:13 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_data	*g_aux_data;

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	set_initial_envp(envp, &data);
	att_exit_status(0, &data);
	att_virtual_envp(&data);
	init_repl(&data);
	end_program(&data);
}
