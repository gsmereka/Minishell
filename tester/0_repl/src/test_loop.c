/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:52:57 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/30 11:36:17 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static void	restore_std_file_descriptors(t_data *data);
static void	make_fork(int test, t_data *data);
static void	execute_test(int test, t_data *data);
static char	**set_valgrind_args(t_data *data);

void	test_input_loop(t_data *data)
{
	int	test;

	test = 0;
	while (test < data->input_tests_amount)
	{
		make_fork(test, data);
		test++;
	}
}

static void	make_fork(int test, t_data *data)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		exit_error(12, "Error at use fork() function\n", data);
	if (pid == 0)
	{
		execute_test(test, data);
		exit_error(1, "", data);
	}
	else
	{
		data->process.pid[test] = pid;
		waitpid(data->process.pid[test],
			&data->process.status[test], WNOHANG | WUNTRACED);
		restore_std_file_descriptors(data);
	}
}

static void	restore_std_file_descriptors(t_data *data)
{
	int	process_1;
	int	process_2;
	int	process_3;

	process_1 = dup2(data->original_stdin, 0);
	process_2 = dup2(data->original_stdout, 1);
	process_3 = dup2(data->original_stder, 2);
	if (process_1 < 0 || process_2 < 0 || process_3 < 0)
		exit_error(2, "Fail at restore file descriptors\n", data);
}

static void	execute_test(int test, t_data *data)
{
	char	**valgrind_args;

	valgrind_args = set_valgrind_args(data);
	redirect_input(test, data);
	redirect_output(test, data);
	redirect_error(test, data);
	execve(data->valgrind_path, valgrind_args, data->envp);
	free(valgrind_args[1]);
	free(valgrind_args);
}

static char	**set_valgrind_args(t_data *data)
{
	char	**valgrind_args;

	valgrind_args = calloc(4, sizeof(char *));
	if (!valgrind_args)
		exit_error(12, "Error at alloc valgrind_args memory\n", data);
	valgrind_args[0] = data->valgrind_path;
	valgrind_args[1] = strdup("--suppressions=readline.supp");
	if (!valgrind_args[1])
		exit_error(12, "Error at alloc valgrind_args memory\n", data);
	valgrind_args[2] = strdup("../minishell");
	if (!valgrind_args[2])
		exit_error(12, "Error at alloc valgrind_args memory\n", data);
	return (valgrind_args);
}
