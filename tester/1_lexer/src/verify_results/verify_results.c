/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_results.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 13:02:25 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tester.h"

static void	reopen_user_outputs(t_data *g_data);
static void	verification_loop(t_data *g_data);
static int	compare_outputs(int test, t_data *g_data);
static void	print_result(int result, int leaks, int test);

void	verify_results(t_data *g_data)
{
	reopen_user_outputs(g_data);
	verification_loop(g_data);
}

static void	verification_loop(t_data *g_data)
{
	int	test;
	int	result;
	int	leaks;

	test = 0;
	while (test < g_data->input_tests_amount)
	{
		result = compare_outputs(test, g_data);
		leaks = check_leaks(test, g_data);
		print_result(result, leaks, test);
		test++;
	}
}

static int	compare_outputs(int test, t_data *g_data)
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
		status_1 = read(g_data->expected_outputs_fd[test], &expected, 1);
		status_2 = read(g_data->user_outputs_fd[test], &user, 1);
		if (status_1 < 0 || status_2 < 0)
			return (0);
		if (expected[0] != user[0])
			return (0);
	}
	return (1);
}

static void	print_result(int result, int leaks, int test)
{
	printf("Test %d:", test);
	if (result)
		printf(" OK /");
	else
		printf(" KO /");
	if (leaks)
		printf(" leaks\n");
	else
		printf(" No Leaks\n");
}

static void	reopen_user_outputs(t_data *g_data)
{
	int	i;

	i = 0;
	while (i < g_data->input_tests_amount)
	{
		close(g_data->user_outputs_fd[i]);
		close(g_data->user_error_fd[i]);
		g_data->user_outputs_fd[i] = open(g_data->user_outputs_name[i], O_RDONLY);
		g_data->user_error_fd[i] = open(g_data->user_error_name[i], O_RDONLY);
		if (g_data->user_outputs_fd[i] < 0 || g_data->user_error_fd[i] < 0)
			exit_error(2, "Fail at reopen file\n", g_data);
		i++;
	}
}
