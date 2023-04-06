/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:50 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/06 17:19:07 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	set_exit_status(char **args, t_data *data);
static int	valid_args(char **args, t_data *data);
static int	is_default_value(char *arg, t_data *data);
static void	execute_exit(t_data *data);

void	ft_exit(char **args, t_data *data)
{
	long int	exit_status;

	if (!valid_args(args, data))
		return ;
	else if (args && args[1])
		exit_status = set_exit_status(args, data);
	else
		exit_status = 0;
	att_exit_status(exit_status, data);
	execute_exit(data);
}

static int	valid_args(char **args, t_data *data)
{
	char		*error_msg;

	if (args && !args[1])
		return (1);
	if (args && args[1] && args [2])
	{
		error_msg = "bash: exit: too many arguments\n";
		write(2, error_msg, ft_strlen(error_msg));
		att_exit_status(1, data);
		return (0);
	}
	if (is_default_value(args[1], data))
		execute_exit(data);
	if (!check_if_is_numeric(args[1])
		|| !check_integer_size(ft_atoli(args[1]), args[1]))
	{
		error_msg = ft_strjoin("bash: exit: ", args[1]);
		write(2, error_msg, ft_strlen(error_msg));
		error_msg = ": numeric argument required\n";
		write(2, error_msg, ft_strlen(error_msg));
		att_exit_status(2, data);
		execute_exit(data);
	}
	return (1);
}

static int	set_exit_status(char **args, t_data *data)
{
	long int	exit_status;

	(void)data;
	exit_status = ft_atoli(args[1]);
	if (exit_status < 0)
		exit_status = 156;
	return (exit_status);
}

static int	is_default_value(char *arg, t_data *data)
{
	if (ft_strcmp(arg, "-9223372036854775808") == 0)
	{
		att_exit_status(0, data);
		return (1);
	}
	else if (ft_strcmp(arg, "-9223372036854775807") == 0)
	{
		att_exit_status(1, data);
		return (1);
	}
	return (0);
}

static void	execute_exit(t_data *data)
{
	ft_putstr_fd("exit\n", 2);
	close(data->output_save_fd);
	close(data->input_save_fd);
	close(1);
	close(0);
	end_program(data);
}
