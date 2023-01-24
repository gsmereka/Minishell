/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/24 20:04:20 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

void	wait_tests(t_data *data);

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	initialize(envp, &data);
	test_input_loop(&data);
	wait_tests(&data);
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
