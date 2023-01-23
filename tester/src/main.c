/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:36:24 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/23 10:20:46 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	initialize(&data);
	printf("Mundo Oi\n");
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

void	input_loop(t_data *data)
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
	int pid = fork();

	if (pid == 0)
	{
		redirecionar_entrada_do_teste()
		redirecionar_saida_do_minishel()
		execve("../minishell", NULL, NULL);
	}
}