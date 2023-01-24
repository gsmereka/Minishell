/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:10:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/24 20:25:17 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

void	set_files(t_data *data);
void	open_files(t_data *data);
void	save_standart_input_and_output(t_data *data);
static void allocate_memory(t_data *data);
char	*ft_strjoin(char const *s1, char const *s2);

void	initialize(char *envp[], t_data *data)
{
	data->envp = envp;
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
	int		i;
	char	*ver;

	i = 0;
	while (i < data->input_tests_amount)
	{
		ver = ft_itoa(i);
		data->input_tests_name[i] = ft_strjoin("./tests/input_tests/test_", ver);
		data->expected_outputs_name[i] = ft_strjoin("./tests/input_tests/test_", ver);
		data->user_outputs_name[i] = ft_strjoin("./tests/input_tests/test_", ver);
		free(ver);
		if (!data->input_tests_name[i] || data->expected_outputs_name[i] || data->user_outputs_name[i])
			exit_error(12, "Fail at allocate test_file paths\n", data);
		i++;
	}
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

char	*ft_strjoin(char const *s1, char const *s2)
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
