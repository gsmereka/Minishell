/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:52:57 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static void	restore_std_file_descriptors(t_data *g_data);
static void	make_fork(int test, t_data *g_data);
static void	execute_test(int test, t_data *g_data);
static char	**set_valgrind_args(t_data *g_data);

void	test_input_loop(t_data *g_data)
{
	int	test;

	test = 0;
	while (test < g_data->input_tests_amount)
	{
		make_fork(test, g_data);
		test++;
	}
}

static void	make_fork(int test, t_data *g_data)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		exit_error(12, "Error at use fork() function\n", g_data);
	if (pid == 0)
	{
		execute_test(test, g_data);
		exit_error(1, "", g_data);
	}
	else
	{
		g_data->process.pid[test] = pid;
		waitpid(g_data->process.pid[test],
			&g_data->process.status[test], WNOHANG | WUNTRACED);
		restore_std_file_descriptors(g_data);
	}
}

static void	restore_std_file_descriptors(t_data *g_data)
{
	int	process_1;
	int	process_2;
	int	process_3;

	process_1 = dup2(g_data->original_stdin, 0);
	process_2 = dup2(g_data->original_stdout, 1);
	process_3 = dup2(g_data->original_stder, 2);
	if (process_1 < 0 || process_2 < 0 || process_3 < 0)
		exit_error(2, "Fail at restore file descriptors\n", g_data);
}

static void	execute_test(int test, t_data *g_data)
{
	char	**valgrind_args;

	valgrind_args = set_valgrind_args(g_data);
	redirect_input(test, g_data);
	redirect_output(test, g_data);
	redirect_error(test, g_data);
	execve(g_data->valgrind_path, valgrind_args, g_data->envp);
	free(valgrind_args[1]);
	free(valgrind_args);
}

static char	**set_valgrind_args(t_data *g_data)
{
	char	**valgrind_args;

	valgrind_args = calloc(4, sizeof(char *));
	if (!valgrind_args)
		exit_error(12, "Error at alloc valgrind_args memory\n", g_data);
	valgrind_args[0] = g_data->valgrind_path;
	valgrind_args[1] = strdup("--suppressions=readline.supp");
	if (!valgrind_args[1])
		exit_error(12, "Error at alloc valgrind_args memory\n", g_data);
	valgrind_args[2] = strdup("../minishell");
	if (!valgrind_args[2])
		exit_error(12, "Error at alloc valgrind_args memory\n", g_data);
	return (valgrind_args);
}
