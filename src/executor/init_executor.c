/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/08 11:00:33 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_executor(t_data *data)
{
	if (!data->tokens)
		return ;
	get_commands_info(data);
	
}
