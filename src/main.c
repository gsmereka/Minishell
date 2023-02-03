/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:30:54 by gde-mora          #+#    #+#             */
/*   Updated: 2023/01/30 13:11:16 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// :)
#include "../headers/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.envp = envp;
	init_repl(&data);
	ft_printf("Hello Mundo\n");
}
