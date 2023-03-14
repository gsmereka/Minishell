/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:10:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tester.h"

static void	open_files(t_data *g_data);
static void	save_standart_file_descriptors(t_data *g_data);
static void	allocate_memory(t_data *g_data);

void	initialize(char *envp[], t_data *g_data)
{
	g_data->envp = envp;
	allocate_memory(g_data);
	set_files(g_data);
	open_files(g_data);
	save_standart_file_descriptors(g_data);
}

static void	allocate_memory(t_data *g_data)
{
	g_data->valgrind_path = NULL;
	g_data->paths = NULL;
	g_data->process.pid = calloc(g_data->input_tests_amount + 1, sizeof(int));
	g_data->process.status = calloc(g_data->input_tests_amount + 1, sizeof(int));
	g_data->input_tests_fd = calloc(g_data->input_tests_amount + 1, sizeof(int));
	g_data->expected_outputs_fd
		= calloc(g_data->input_tests_amount + 1, sizeof(int));
	g_data->user_error_fd = calloc(g_data->input_tests_amount + 1, sizeof(int));
	g_data->user_outputs_fd = calloc(g_data->input_tests_amount + 1, sizeof(int));
	g_data->input_tests_name
		= calloc(g_data->input_tests_amount + 1, sizeof(char *));
	g_data->expected_outputs_name
		= calloc(g_data->input_tests_amount + 1, sizeof(char *));
	g_data->user_outputs_name
		= calloc(g_data->input_tests_amount + 1, sizeof(char *));
	g_data->user_error_name
		= calloc(g_data->input_tests_amount + 1, sizeof(char *));
	if (!g_data->input_tests_fd || !g_data->input_tests_name
		|| !g_data->user_outputs_name
		|| !g_data->expected_outputs_name
		|| !g_data->expected_outputs_fd || !g_data->user_outputs_fd
		|| !g_data->process.pid || !g_data->process.status
		|| !g_data->user_error_fd || !g_data->user_error_name)
		exit_error(12, "Fail at allocate initial memory\n", g_data);
}

static void	save_standart_file_descriptors(t_data *g_data)
{
	g_data->original_stdin = dup(0);
	g_data->original_stdout = dup(1);
	g_data->original_stder = dup(2);
}

static void	open_files(t_data *g_data)
{
	int	i;

	i = 0;
	while (i < g_data->input_tests_amount)
	{
		g_data->input_tests_fd[i] = open(g_data->input_tests_name[i], O_RDONLY);
		g_data->expected_outputs_fd[i]
			= open(g_data->expected_outputs_name[i], O_RDONLY);
		g_data->user_outputs_fd[i] = open(g_data->user_outputs_name[i],
				O_RDWR | O_CREAT | O_TRUNC, 0777);
		g_data->user_error_fd[i]
			= open(g_data->user_error_name[i], O_RDWR | O_CREAT | O_TRUNC, 0777);
		if (g_data->input_tests_fd[i] < 0 || g_data->expected_outputs_fd[i] < 0
			|| g_data->user_outputs_fd[i] < 0 || g_data->user_error_fd[i] < 0)
			exit_error(1, "Fail at open files\n", g_data);
		i++;
	}
}
