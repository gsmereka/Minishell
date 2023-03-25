/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:50 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/25 11:54:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_exit(char **args, t_data *data)
{
	(void)args;
	ft_putstr_fd("exit\n", 2);
	att_exit_status(0, data);
	close(1);
	close(0);
	end_program(data);
}
