/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/30 13:11:39 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

// static void	repl_loop(t_data *data);

void	init_repl(t_data *data)
{
	(void)data;
	ft_printf("Hello Mundo\n");
	exit(0);
}

// static void	repl_loop(t_data *data)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// 	(void)data;
// 	// close(0);
// 	// str = readline(NULL);
// 	// // 	// ft_printf("%s\n", str);
// 	// add_history(str);
// 	// free(str);
// 	while (i < 3)
// 	{
// 		str = readline("Jose Carlos e Compania:");
// 		// int	pid;

// 		// pid = fork();
// 		// if (pid == 0)
// 		// 	execve("/bin/clear", NULL, data->envp);
// 		add_history(str);
// 		// ft_printf("%s\n", str);
// 		free(str);
// 		i++;
// 	}
// 	rl_clear_history();
// }
