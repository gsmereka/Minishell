/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:30:54 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/04 19:36:08 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	ft_bzero(&data, sizeof(t_data));
	set_initial_envp(envp, &data);
	att_envp_exitstatus_var(&data);
	att_virtual_envp(&data);
	init_repl(&data);
	end_program(&data);

	/* quando o export cria uma env nova, ele coloca no começo? pq no final é sempre o caminho /env
	   remover comentarios em portugues -- ou traduzir p ingles
	*/
}
