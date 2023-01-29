/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/28 23:32:21 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	repl_loop(t_data *data);

void	init_repl(char *envp[], t_data *data)
{
	(void)envp;
	(void)data;
	repl_loop(data);
	ft_printf("Hello Mundo\n");
	exit(0);
}

static void	repl_loop(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	(void)data;
	int	pid;

	pid = fork();
	if (pid != 0)
		exit(0);
	while (i < 3)
	{
		str = readline("");
		// ft_printf("%s\n", str);
		free(str);
		i++;
	}
}
