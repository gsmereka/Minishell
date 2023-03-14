/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:27:57 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_cd_error_msg(int	error, char *name, t_data *g_data)
{
	char		*error_msg;

	if (error == 1)
	{
		error_msg = "bash: cd: too many arguments\n"; //incluir nome
		write(2, error_msg, ft_strlen(error_msg));
		g_data->exit_status = 1;
		return ;
	}
	if (error == 2)
	{
		error_msg = "bash: cd: Not a directory\n"; //incluir nome
		write(2, error_msg, ft_strlen(error_msg));
		g_data->exit_status = 1;
		return ;
	}
	if (error == 3)
	{
		// bash: cd: Makefile: Not a directory
		error_msg = "bash: cd: Permission denied\n"; //incluir nome
		write(2, error_msg, ft_strlen(error_msg));
		g_data->exit_status = 1;
		return ;
	}
}
