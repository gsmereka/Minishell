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
static void	save_history(char *str);
static void	init_repl_signals(t_data *data);
static void	signal_handler(int signal);

void	init_repl(t_data *data)
{
	init_loop(data);
	exit(0);
}

static void	init_loop(t_data *data)
{
	char	*str;
	int		i;

	i = 0;
	init_repl_signals(data);
	while (1)
	{
		str = readline("Hopeshell:$ ");
		if (!str)
		{
			ft_printf("exit\n");
			break ;
		}
		if (!ft_strncmp("exit", str, 4))
		{
			free(str);
			break ;
		}
		rl_on_new_line();
		save_history(str);
		free(str);
		i++;
	}
	rl_clear_history();
}

static void	save_history(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == ' ')
		i++;
	if (str[i] != '\0')
		add_history(str);
}

static void	init_repl_signals(t_data *data)
{
	struct sigaction	ctrl_c;
	struct sigaction	ctrl_backsslash;

	(void)data;
	ctrl_c.sa_handler = signal_handler;
	ctrl_backsslash.sa_handler = signal_handler;
	sigaction(SIGINT, &ctrl_c, NULL);
	sigaction(SIGQUIT, &ctrl_backsslash, NULL);
	ft_printf("init signals\n");
}

static void	signal_handler(int signal)
{
	if (signal == SIGINT)
		ft_printf("Buenos Dias\n");
	else
		ft_printf("Bolos");
}
