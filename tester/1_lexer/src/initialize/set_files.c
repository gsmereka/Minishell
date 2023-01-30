/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:23:06 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/27 22:28:55 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tester.h"

static void	set_files_path(int file, t_data *data);

// O ft_Strjoin não libera memoria
void	set_files(t_data *data)
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
