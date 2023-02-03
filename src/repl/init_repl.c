/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/31 13:24:03 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	init_loop(t_data *data);
static void	save_history(char *readline_buffer);
static void	init_repl_signals(t_data *data);
static void	handle_ctrl_c(int signal);

void	init_repl(t_data *data)
{
	data->prompt = "HopeShell:$ ";
	data->readline_buffer = NULL;
	init_repl_signals(data);
	init_loop(data);
	exit(0);
}

static void	init_loop(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		data->readline_buffer = readline(data->prompt);
		if (!data->readline_buffer)
		{
			ft_printf("exit\n");
			break ;
		}
		if (!ft_strncmp("exit", data->readline_buffer, 4))
		{
			break ;
		}
		rl_on_new_line();
		save_history(data->readline_buffer);
		if (data->readline_buffer)
			free(data->readline_buffer);
		i++;
	}
	rl_clear_history();
}

static void	save_history(char *readline_buffer)
{
	int	i;

	i = 0;
	while (readline_buffer[i] == '\t' || readline_buffer[i] == ' ')
		i++;
	if (readline_buffer[i] != '\0')
		add_history(readline_buffer);
}

static void	init_repl_signals(t_data *data)
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
