/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:39 by gsmereka          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/04 19:39:16 by gsmereka         ###   ########.fr       */
=======
/*   Updated: 2023/03/22 16:55:48 by gsmereka         ###   ########.fr       */
>>>>>>> executor_merged
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	identify_flags(char **args);
static void	display_text_line(char **args);

void	ft_echo(char **args, t_data *data)
{
	int	n_flag;

	(void)data;
	if (!args)
		return ;
<<<<<<< HEAD
	identify_flags(&n_flag, args);
	display_text_line(&n_flag, args);
	(void)data;
=======
	n_flag = identify_flags(args);
	if (!n_flag)
	{
		display_text_line(args);
		ft_putstr_fd("\n", 1);
	}
	else
		display_text_line(args + 1);
>>>>>>> executor_merged
}

static int	identify_flags(char **args)
{
	if (!args[1])
		return (0);
	if (ft_strncmp(args[1], "-n", 2) == 0)
		return (1);
	return (0);
}

static void	display_text_line(char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}
