/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/25 13:59:23 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

void	wait_tests(t_data *data);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	initialize(envp, &data);
	set_valgrind_path(&data);
	test_input_loop(&data);
	wait_tests(&data); // não ta funcionando direito.
	sleep(3); // isso que ta resolvendo, dá tempo para os arquivos serem escritos.
	verify_results(&data);
	finalize(&data);
}

void	wait_tests(t_data *data)
{
	int	i;

	i = 0;
	if (data->process.pid && data->process.status)
	{
		while (i < data->input_tests_amount)
		{
			if (data->process.pid[i] && data->process.status[i])
				waitpid(data->process.pid[i], &data->process.status[i], WUNTRACED);
			i++;
		}
	}
}
