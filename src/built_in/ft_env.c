/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:44 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/24 13:19:25 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_env(char **args, t_data *data)
{
	t_env	*aux_print;
	int		i;

	(void)args;
	i = 0;
	aux_print = data->dict_envp;
	while (aux_print)
	{
		ft_printf("%s=%s\n", aux_print->key, aux_print->value);
		aux_print = aux_print->next;
		i++;
	}
}
