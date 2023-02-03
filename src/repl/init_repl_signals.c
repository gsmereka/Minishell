/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:15:30 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/03 12:18:10 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	handle_ctrl_c(int signal);

void	init_repl_signals(t_data *data)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_backsslash;

	(void)data;
	ctrl_c.sa_handler = handle_ctrl_c;
	ctrl_backsslash.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ctrl_c, NULL);
	sigaction(SIGQUIT, &ctrl_backsslash, NULL);
}

static void	handle_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
