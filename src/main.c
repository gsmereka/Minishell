/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:30:54 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

t_data	g_data;

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	ft_bzero(&g_data, sizeof(t_data));
	set_initial_envp(envp, &g_data);
	att_envp_exitstatus_var(&g_data);
	att_virtual_envp(&g_data);
	init_repl(&g_data);
	end_program(&g_data);

	/* quando o export cria uma env nova, ele coloca no começo? pq no final é sempre o caminho /env
	   remover comentarios em portugues -- ou traduzir p ingles
	*/
}
