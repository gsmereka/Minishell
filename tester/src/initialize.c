/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:10:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/23 21:46:07 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

void	set_files(t_data *data);
void	open_files(t_data *data);

static void allocate_memory(t_data *data);

void	initialize(t_data *data)
{
	allocate_memory(data);
	set_files(data);
}

static void allocate_memory(t_data *data)
{
	data->input_tests_amount = 3;
	data->input_tests_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->expected_outputs_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->user_outputs_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->input_tests_name = calloc(data->input_tests_amount + 1, sizeof(char *));
	data->expected_outputs_name = calloc(data->input_tests_amount + 1, sizeof(char *));
	data->user_outputs_name = calloc(data->input_tests_amount + 1, sizeof(char *));
	if (!data->input_tests_fd || !data->input_tests_name || !data->user_outputs_name
		 || !data->expected_outputs_name || !data->expected_outputs_fd || !data->user_outputs_fd)
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
		data->input_tests_fd[i] = open(data->input_tests_name[i], O_RDONLY);
		data->expected_outputs_fd[i] = open(data->expected_outputs_name[i], O_RDONLY);
		data->user_outputs_fd[i] = open(data->user_outputs_name[i], O_RDWR | O_TRUNC);
		if (data->input_tests_fd[i] < 0 || data->expected_outputs_fd[i] < 0 || data->user_outputs_fd[i] < 0)
			exit_error(12, "Fail at allocate initial memory\n", data);
	}
}
