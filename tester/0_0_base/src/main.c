/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 19:00:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

void	wait_tests(t_data *data);

/*Variavel definida no Makefile TESTS_AMOUNT
depende de quantos arquivos existem na pasta tests/input_tests/*/

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.input_tests_amount = TESTS_AMOUNT;
	initialize(envp, &data);
	set_valgrind_path(&data);
	test_input_loop(&data);
	wait_tests(&data);
	verify_results(&data);
	finalize(&data);
}

// ainda_não_funciona_direito, o sleep que da tempo suficiente
void	wait_tests(t_data *data)
{
	int	i;

	i = 0;
	sleep(3);
	if (data->process.pid && data->process.status)
	{
		while (i < data->input_tests_amount)
		{
			if (data->process.pid[i] && data->process.status[i])
				waitpid(data->process.pid[i],
					&data->process.status[i], WUNTRACED);
			i++;
		}
	}
}
