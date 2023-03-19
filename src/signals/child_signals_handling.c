/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signals_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 21:08:51 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/19 13:11:56 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern t_data	*g_aux_data;

static void	handle_ctrl_c(int signal);
static void	close_files(int *files);
static void	close_all_fds(t_data *data);

void	child_signals_handling(t_data *data)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_backsslash;

	g_aux_data = data;
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
		ft_putstr_fd("\n", 1);
		if (g_aux_data->exec)
			g_aux_data->exec->need_interrupt = 1;
	}
}

static void	close_all_fds(t_data *data)
{
	int	i;

	i = 0;
	while (data->exec->pipes[i])
	{
		close(data->exec->pipes[i][1]);
		close(data->exec->pipes[i][0]);
		close_files(data->exec->cmds[i]->infiles_fd);
		close_files(data->exec->cmds[i]->outfiles_fd);
		i++;
	}
	// close(1);
	close(0);
}

static void	close_files(int *files)
{
	int	i;

	i = 0;
	if (files)
	{
		while (files[i])
		{
			if (files[i] != -1)
				close (files[i]);
			i++;
		}
	}
}
