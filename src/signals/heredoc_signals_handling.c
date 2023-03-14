/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals_handling.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:08:47 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:49:30 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	data;

static void	handle_ctrl_c(int signal);

void	heredoc_signals_handling()
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_backsslash;

	ft_bzero(&ctrl_c, sizeof(struct sigaction));
	ft_bzero(&ctrl_backsslash, sizeof(struct sigaction));
	ctrl_c.sa_handler = handle_ctrl_c;
	ctrl_backsslash.sa_handler = SIG_IGN;
	sigaction(SIGINT, &ctrl_c, NULL);
	sigaction(SIGQUIT, &ctrl_backsslash, NULL);
}

static void	handle_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\1\n", STDIN_FILENO);
		end_program(&data);
		// ft_putstr_fd("\n", 1);
		// rl_replace_line("", 1);
		// rl_on_new_line();
		// rl_redisplay();
	}
}