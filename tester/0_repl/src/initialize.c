/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:10:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/27 21:02:11 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static void	set_files(t_data *data);
static void	open_files(t_data *data);
static void	save_standart_file_descriptors(t_data *data);
static void	allocate_memory(t_data *data);
static void	set_files_path(int file, t_data *data);
static char	*ft_strjoin(char const *s1, char const *s2);

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

static void	set_files(t_data *data) // O ft_Strjoin não libera memoria
{
	int		i;

	i = 0;
	while (i < data->input_tests_amount)
	{
		set_files_path(i, data);
		if (!data->input_tests_name[i] || !data->expected_outputs_name[i]
			|| !data->user_outputs_name[i] || !data->user_error_name[i])
			exit_error(12, "Fail at allocate test_file paths\n", data);
		i++;
	}
}

static void	set_files_path(int file, t_data *data)
{
	char	*ver;
	char	*input_tests;
	char	*expected_outputs;
	char	*user_outputs;
	char	*user_error;

	ver = ft_itoa(file);
	input_tests = ft_strjoin(LOCAL_PATH, "/tests/input_tests/test_");
	expected_outputs = ft_strjoin(LOCAL_PATH, "/tests/expected_outputs/test_");
	user_outputs = ft_strjoin(LOCAL_PATH, "/tests/user_outputs/test_");
	user_error = ft_strjoin(LOCAL_PATH, "/tests/user_error/test_");
	data->input_tests_name[file]
		= ft_strjoin(input_tests, ver);
	data->expected_outputs_name[file]
		= ft_strjoin(expected_outputs, ver);
	data->user_outputs_name[file]
		= ft_strjoin(user_outputs, ver);
	data->user_error_name[file]
		= ft_strjoin(user_error, ver);
	free(ver);
	free(input_tests);
	free(expected_outputs);
	free(user_outputs);
	free(user_error);
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

static void	save_standart_file_descriptors(t_data *data)
{
	data->original_stdin = dup(0);
	data->original_stdout = dup(1);
	data->original_stder = dup(2);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1_size;
	size_t	s2_size;
	char	*new_s;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_size = strlen(s1);
	s2_size = strlen(s2);
	new_s = (char *)calloc(s1_size + s2_size + 1, sizeof(char));
	while (i < (s1_size + s2_size + 1))
	{
		if (i >= s1_size)
			new_s[i] = s2[i - s1_size];
		else
			new_s[i] = s1[i];
		i++;
	}
	return ((char *)new_s);
}
