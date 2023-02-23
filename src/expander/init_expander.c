/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/23 04:07:23 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*void	set_new_env(t_data *data)    isso ´´e no executor?
{
	int	i;

	i = 0;
	while(data->envp[i])
	{
		ft_printf("%s\n", data->envp[i]);
		i++;
	}
}*/

//tenho q dar bzero nuns ngc pra n quebrar...
//e criar func q libera td

void	init_expander(t_data *data)
{
//	se o usuario mandar alguma nova env
	//set_new_env(data);  //(salva por key e value)
	//se n, n altera nd
	(void)data;
}
