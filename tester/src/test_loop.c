/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:52:57 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/24 23:14:13 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

/* Da forma que o REPL funciona, cada comando termina numa quebra de linha,
entao todos os testes vão estar num unico arquivo de texto, separados por uma quebra de linha natural
Para cada arquivo de teste, vai ter um arquivo contatenando toda a saida esperada.
O obejtivo do tester é comparar a saida do usuario com a saida esperada.
Ao iniciar outra rodada de testes, apagar os outputs de usuario anteriores.
(No futura talvez seria interessante colocar uma flag no tester, para identificar qual etapa do codigo
estamos testando)

depois fazer uma rechecagem buscando vazamentos*/

void	restore_input_and_output_error(int test, t_data *data);
void	execute_test(int test, t_data *data);

void	test_input_loop(t_data *data)
{
	int	test;

	test = 0;
	while (test < data->input_tests_amount)
	{
		execute_test(test, data);
		test++;
	}
}

void	execute_test(int test, t_data *data)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		exit_error(12, "Error at use fork() function\n", data);
	if (pid == 0)
	{
		char	**args;

		args = calloc(3, sizeof(char *));
		if (!args)
			exit_error(12, "Error at alloc valgrind args memory\n", data);
		redirect_input(test, data);
		redirect_output(test, data);
		redirect_error(test, data);
		args[0] = data->valgrind_path;
		args[1] = strdup("../minishell");
		args[2] = NULL;
		execve(data->valgrind_path, args, data->envp);
		free(args[1]);
		free(args);
		exit_error(1, "", data);
	}
	else
	{
		data->process.pid[test] = pid;
		waitpid(data->process.pid[test],
			&data->process.status[test], WNOHANG | WUNTRACED);
		restore_input_and_output_error(test, data);
	}
}

void	restore_input_and_output_error(int test, t_data *data)
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
