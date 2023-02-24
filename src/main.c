/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:30:54 by gde-mora          #+#    #+#             */
/*   Updated: 2023/02/24 13:17:51 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// :)
#include "../headers/minishell.h"

static void	print_envp(t_data *data);

void	free_data(t_data *data)
{
	if (data->dict_envp)
		dictclear(data->dict_envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	ft_bzero(&data, sizeof(t_data));
	set_initial_envp(envp, &data);
	init_repl(&data);
	free_data(&data); //a cada exit tem q liberar tbm
	end_program(&data);
}

static void	print_envp(t_data *data)
{
	int	i;

	t_env *aux_print = data->dict_envp;
	i = 0;
	while (aux_print)
	{
		if (ft_strncmp(aux_print->key, "PWD", 4) == 0)
			ft_printf("key: %s\nvalor:%s\n", aux_print->key, aux_print->value);
		aux_print = aux_print->next;
		i++;
	}
}
