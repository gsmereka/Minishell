/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:08:51 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/21 13:30:51 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	*g_aux_data;

static void	handle_ctrl_c(int signal);
static void	handle_backslash(int signal);

void	child_signals_handling(t_data *data)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_backslash;

	g_aux_data = data;
	ft_bzero(&ctrl_c, sizeof(struct sigaction));
	ft_bzero(&ctrl_backslash, sizeof(struct sigaction));
	ctrl_c.sa_handler = handle_ctrl_c;
	ctrl_backslash.sa_handler = handle_backslash;
	sigaction(SIGINT, &ctrl_c, NULL);
	sigaction(SIGQUIT, &ctrl_backslash, NULL);
}

static void	handle_ctrl_c(int signal)
{
	if (signal == SIGINT)
	{
		att_envp_exitstatus_var(130, g_aux_data);
		ft_putstr_fd("\n", 1);
		if (g_aux_data->exec)
			g_aux_data->exec->need_interrupt = 1;
	}
}

static void	handle_backslash(int signal)
{
	if (signal == SIGQUIT)
	{
		att_envp_exitstatus_var(131, g_aux_data);
		ft_putstr_fd("Quit\n", 1);
		if (g_aux_data->exec)
			g_aux_data->exec->need_interrupt = 1;
	}
}
