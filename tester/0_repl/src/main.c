/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

void	wait_tests(t_data *g_data);

/*Variavel definida no Makefile TESTS_AMOUNT
depende de quantos arquivos existem na pasta tests/input_tests/*/

int	main(int argc, char *argv[], char *envp[])
{
	t_data	g_data;

	(void)argc;
	(void)argv;
	g_data.input_tests_amount = TESTS_AMOUNT;
	initialize(envp, &g_data);
	set_valgrind_path(&g_data);
	test_input_loop(&g_data);
	wait_tests(&g_data);
	verify_results(&g_data);
	finalize(&g_data);
}

// ainda_não_funciona_direito, o sleep que da tempo suficiente
void	wait_tests(t_data *g_data)
{
	int	i;

	i = 0;
	sleep(3);
	if (g_data->process.pid && g_data->process.status)
	{
		while (i < g_data->input_tests_amount)
		{
			if (g_data->process.pid[i] && g_data->process.status[i])
				waitpid(g_data->process.pid[i],
					&g_data->process.status[i], WUNTRACED);
			i++;
		}
	}
}
