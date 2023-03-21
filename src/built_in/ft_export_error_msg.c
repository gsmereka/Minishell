/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_error_msg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:29:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/21 20:25:06 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_export_error_msg(int error, char *name, t_data *data)
{
	char		*error_msg;

	if (error == 1)
	{
		error_msg = ft_strjoin("bash: export: `", name);
		write(2, error_msg, ft_strlen(error_msg));
		free(error_msg);
		error_msg = "': not a valid identifier\n";
		write(2, error_msg, ft_strlen(error_msg));
		att_exit_status(1, data);
		return ;
	}
}
