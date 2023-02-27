/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:46:14 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/27 16:09:37 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	execute_built_in(t_data *data)
{
	char	**args;

	args = ft_split(data->user_input, ' ');
	if (!args)
		return ;
	else if (!args[0])
	{
		free(args);
		return ;
	}
	else if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		ft_echo(args, data);
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		ft_cd(args, data);
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		ft_env(args, data);
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		ft_exit(args, data);
	else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		ft_pwd(args, data);
	else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		ft_export(args, data);
	else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		ft_unset(args, data);
	free_array_list((void **)args);
}
