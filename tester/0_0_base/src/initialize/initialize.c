/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:10:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 19:00:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tester.h"

static void	open_files(t_data *data);
static void	save_standart_file_descriptors(t_data *data);
static void	allocate_memory(t_data *data);

void	initialize(char *envp[], t_data *data)
{
	data->envp = envp;
	allocate_memory(data);
	set_files(data);
	open_files(data);
	save_standart_file_descriptors(data);
}

static void	allocate_memory(t_data *data)
{
	data->valgrind_path = NULL;
	data->paths = NULL;
	data->process.pid = calloc(data->input_tests_amount + 1, sizeof(int));
	data->process.status = calloc(data->input_tests_amount + 1, sizeof(int));
	data->input_tests_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->expected_outputs_fd
		= calloc(data->input_tests_amount + 1, sizeof(int));
	data->user_error_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->user_outputs_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->input_tests_name
		= calloc(data->input_tests_amount + 1, sizeof(char *));
	data->expected_outputs_name
		= calloc(data->input_tests_amount + 1, sizeof(char *));
	data->user_outputs_name
		= calloc(data->input_tests_amount + 1, sizeof(char *));
	data->user_error_name
		= calloc(data->input_tests_amount + 1, sizeof(char *));
	if (!data->input_tests_fd || !data->input_tests_name
		|| !data->user_outputs_name
		|| !data->expected_outputs_name
		|| !data->expected_outputs_fd || !data->user_outputs_fd
		|| !data->process.pid || !data->process.status
		|| !data->user_error_fd || !data->user_error_name)
		exit_error(12, "Fail at allocate initial memory\n", data);
}

static void	save_standart_file_descriptors(t_data *data)
{
	data->original_stdin = dup(0);
	data->original_stdout = dup(1);
	data->original_stder = dup(2);
}

static void	open_files(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input_tests_amount)
	{
		data->input_tests_fd[i] = open(data->input_tests_name[i], O_RDONLY);
		data->expected_outputs_fd[i]
			= open(data->expected_outputs_name[i], O_RDONLY);
		data->user_outputs_fd[i] = open(data->user_outputs_name[i],
				O_RDWR | O_CREAT | O_TRUNC, 0777);
		data->user_error_fd[i]
			= open(data->user_error_name[i], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (data->input_tests_fd[i] < 0 || data->expected_outputs_fd[i] < 0
			|| data->user_outputs_fd[i] < 0 || data->user_error_fd[i] < 0)
			exit_error(1, "Fail at open files\n", data);
		i++;
	}
}
