/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/23 22:40:18 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	initialize(&data);
	printf("Mundo Oi\n");
	test_input_loop(&data);
	finalize(&data);
}

/* Da forma que o REPL funciona, cada comando termina numa quebra de linha,
entao todos os testes vão estar num unico arquivo de texto, separados por uma quebra de linha natural
Para cada arquivo de teste, vai ter um arquivo contatenando toda a saida esperada.
O obejtivo do tester é comparar a saida do usuario com a saida esperada.
Ao iniciar outra rodada de testes, apagar os outputs de usuario anteriores.
(No futura talvez seria interessante colocar uma flag no tester, para identificar qual etapa do codigo
estamos testando)

depois fazer uma rechecagem buscando vazamentos*/

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
	int	pid;

	pid = fork();
	if (pid == -1)
		exit_error(12, "Error at use fork() function", data);
	if (pid == 0)
	{
		redirect_input(test, data);
		redirect_output(test, data);
		// execve("../minishell", NULL, NULL);
	}
	else
	{
		data->process.pid[test] = pid;
		waitpid(data->process.pid[test],
			&data->process.status[test], WNOHANG | WUNTRACED);
	}
}