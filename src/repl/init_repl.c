/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/31 12:22:21 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	init_loop(t_data *data);

void	init_repl(t_data *data)
{
	init_loop(data);
	ft_printf("Hello Mundo\n");
	exit(0);
}

static void	init_loop(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	(void)data;
	while (1)
	{
		str = readline("Hopeshell:$ ");
		if (!ft_strncmp("exit", str, 4))
		{
			free(str);
			break ;
		}
		add_history(str);
		// ft_printf("%s\n", str);
		free(str);
		i++;
	}
	rl_clear_history();
}
