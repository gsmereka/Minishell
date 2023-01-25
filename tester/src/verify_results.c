/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_results.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:02:25 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/24 22:28:39 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static void	verification_loop(t_data *data);
static int	compare_outputs(int test, t_data *data);
static void	check_leaks(int test, t_data *data);
static void	print_result(int result, int test, t_data *data);
static void reopen_user_outputs(t_data *data);

void	verify_results(t_data *data)
{
	sleep(3);
	reopen_user_outputs(data);
	verification_loop(data);
}

static void	verification_loop(t_data *data)
{
	int	test;
	int	result;

	test = 0;
	while (test < data->input_tests_amount)
	{
		result = compare_outputs(test, data);
		print_result(result, test, data);
		check_leaks(test, data);
		test++;
	}
}

static int	compare_outputs(int test, t_data *data)
{
	int		status_1;
	int		status_2;
	char	expected[1];
	char	user[1];

	expected[0] = 0;
	user[0] = 0;
	status_1 = 1;
	status_2 = 1;
	while (status_1)
	{
		status_1 = read(data->expected_outputs_fd[test], &expected, 1);
		status_2 = read(data->user_outputs_fd[test], &user, 1);
		if (status_1 < 0 || status_2 < 0)
			return (0);
		if (expected[0] != user[0])
			return (0);
	}
	return (1);
}

static void	print_result(int result, int test, t_data *data)
{
	printf("Test %d:", test);
	if (result)
		printf(" OK\n");
	else
		printf(" KO\n");
}

static void	reopen_user_outputs(t_data *data)
{
	int i;

	i = 0;
	while (i < data->input_tests_amount)
	{
		close(data->user_outputs_fd[i]);
		data->user_outputs_fd[i] = open(data->user_outputs_name[i], O_RDONLY);
		if (data->user_outputs_fd[i] < 0)
			exit_error(2, "Fail at reopen file\n", data);
		i++;
	}
}

static void	check_leaks(int test, t_data *data)
{
	printf("Leaks\n");
	// printf("No Leaks\n");
}
