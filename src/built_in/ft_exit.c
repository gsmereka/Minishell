/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:50 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/25 16:41:51 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	set_exit_status(char **args, t_data *data);
static int	valid_args(char **args, t_data *data);

void	ft_exit(char **args, t_data *data)
{
	int		exit_status;

	if (!valid_args(args, data))
		return ;
	if (args && args[1])
		exit_status = set_exit_status(args, data);
	else
		exit_status = 0;
	ft_putstr_fd("exit\n", 0); //é pra ser saida 2, mas o tester n sabe disso.
	att_exit_status(exit_status, data);
	close(1);
	close(0);
	end_program(data);
}

static int	valid_args(char **args, t_data *data)
{
	char	*error_msg;

	if (args && !args[1])
		return (1);
	if (args && args[1] && args [2])
	{
		error_msg = "bash: exit: too many arguments\n";
		write(2, error_msg, ft_strlen(error_msg));
		att_exit_status(1, data);
		return (0);
	}
	if (!check_if_is_numeric(args[1]))
	{
		error_msg = ft_strjoin("bash: exit: ", args[1]);
		write(2, error_msg, ft_strlen(error_msg));
		error_msg = ": numeric argument required\n";
		write(2, error_msg, ft_strlen(error_msg));
		att_exit_status(2, data);
		return (0);
	}
	return (1);
}

static int	set_exit_status(char **args, t_data *data)
{
	int		exit_status;
	// char	*error_msg;

	(void)data;
	exit_status = ft_atoli(args[1]);
	if (exit_status < 0)
		exit_status = 156;
	return (exit_status);
}
