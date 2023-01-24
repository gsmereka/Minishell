/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:10:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/24 13:32:47 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

void	set_files(t_data *data);
void	open_files(t_data *data);
void	save_standart_input_and_output(t_data *data);

static void allocate_memory(t_data *data);

void	initialize(t_data *data)
{
	allocate_memory(data);
	set_files(data);
	open_files(data);
	save_standart_input_and_output(data);
}

static void allocate_memory(t_data *data)
{
	data->input_tests_amount = 3;
	data->process.pid = calloc(data->input_tests_amount + 1, sizeof(int));
	data->process.status = calloc(data->input_tests_amount + 1, sizeof(int));
	data->input_tests_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->expected_outputs_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->user_outputs_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->input_tests_name = calloc(data->input_tests_amount + 1, sizeof(char *));
	data->expected_outputs_name = calloc(data->input_tests_amount + 1, sizeof(char *));
	data->user_outputs_name = calloc(data->input_tests_amount + 1, sizeof(char *));
	if (!data->input_tests_fd || !data->input_tests_name || !data->user_outputs_name
		|| !data->expected_outputs_name || !data->expected_outputs_fd || !data->user_outputs_fd
		|| !data->process.pid || !data->process.status)
		exit_error(12, "Fail at allocate initial memory\n", data);
}

void	set_files(t_data *data)
{
	data->input_tests_name[0] = strdup("./tests/input_tests/test_0");
	data->input_tests_name[1] = strdup("./tests/input_tests/test_1");
	data->input_tests_name[2] = strdup("./tests/input_tests/test_2");

	data->expected_outputs_name[0] = strdup("./tests/expected_outputs/test_0");
	data->expected_outputs_name[1] = strdup("./tests/expected_outputs/test_1");
	data->expected_outputs_name[2] = strdup("./tests/expected_outputs/test_2");

	data->user_outputs_name[0] = strdup("./tests/user_outputs/test_0");
	data->user_outputs_name[1] = strdup("./tests/user_outputs/test_1");
	data->user_outputs_name[2] = strdup("./tests/user_outputs/test_2");
}

void	open_files(t_data *data)
{
	int i;

	i = 0;
	while (i < data->input_tests_amount)
	{
		if (!data->input_tests_name[i] || !data->expected_outputs_name[i] || !data->user_outputs_name[i])
			exit_error(1, "Fail at open files\n", data);
		data->input_tests_fd[i] = open(data->input_tests_name[i], O_RDONLY);
		data->expected_outputs_fd[i] = open(data->expected_outputs_name[i], O_RDONLY);
		data->user_outputs_fd[i] = open(data->user_outputs_name[i], O_RDWR | O_TRUNC);
		// printf("i - %d\ne - %d\nu - %d\n", data->input_tests_fd[i], data->expected_outputs_fd[i], data->user_outputs_fd[i]);
		if (data->input_tests_fd[i] < 0 || data->expected_outputs_fd[i] < 0 || data->user_outputs_fd[i] < 0)
			exit_error(1, "Fail at open files\n", data);
		i++;
	}
}

void	save_standart_input_and_output(t_data *data)
{
	data->original_stdin = dup(0);
	data->original_stdout = dup(1);
}
