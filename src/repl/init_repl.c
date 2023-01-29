/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_repl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 23:09:03 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/28 23:14:20 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_repl(char *envp[], t_data *data)
{
	(void)envp;
	(void)data;
	ft_printf("Hello Mundo\n");
	exit(0);
}
