/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl_signals_handling.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 12:15:30 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/20 21:02:31 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	*g_aux_data;

static void	handle_ctrl_c(int signal);

void	init_repl_signals_handling(t_data *data)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_backslash;

	g_aux_data = data;
	ft_bzero(&ctrl_c, sizeof(struct sigaction));
	ft_bzero(&ctrl_backslash, sizeof(struct sigaction));
	ctrl_c.sa_handler = handle_ctrl_c;
	ctrl_backslash.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ctrl_c, NULL);
	sigaction(SIGQUIT, &ctrl_backslash, NULL);
}

static void	handle_ctrl_c(int signal)
{
	if (signal != SIGINT)
		return ;
	ft_putchar_fd('\n', 0);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
