/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:27:57 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/21 20:29:50 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_cd_error_msg(int error, char *name, t_data *data)
{
	char		*error_msg;

	if (error == 1)
	{
		error_msg = "bash: cd: too many arguments\n";
		write(2, error_msg, ft_strlen(error_msg));
	}
	else if (error == 2)
	{
		error_msg = ft_strjoin("bash: cd: ", name);
		write(2, error_msg, ft_strlen(error_msg));
		error_msg = ": Not a directory\n";
		write(2, error_msg, ft_strlen(error_msg));
	}
	else if (error == 3)
	{
		error_msg = ft_strjoin("bash: cd: ", name);
		write(2, error_msg, ft_strlen(error_msg));
		error_msg = ": Permission denied\n";
		write(2, error_msg, ft_strlen(error_msg));
	}
	att_exit_status(1, data);
}
