/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:02:44 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/21 20:08:41 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ft_env(char **args, t_data *data)
{
	char	**envp;
	int		i;

	(void)args;
	i = 0;
	envp = data->virtual_envp;
	if (!envp)
		return ;
	while (envp[i])
	{
		if (envp[i][0] == '?' && envp[i][1] == '=')
			i++;
		else
		{
			ft_printf("%s\n", envp[i]);
			i++;
		}
	}
}
