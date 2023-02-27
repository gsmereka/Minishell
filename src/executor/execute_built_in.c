/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:46:14 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/27 12:56:32 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	execute_built_in(t_data *data)
{
	char	**args;

	args = ft_split(data->user_input, ' ');
	if (strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		ft_echo(args, data);
	if (strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		ft_cd(args, data);
	if (strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		ft_env(args, data);
	if (strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		ft_exit(args, data);
	if (strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		ft_pwd(args, data);
	if (strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		ft_export(args, data);
	if (strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		ft_unset(args, data);
	free_array_list((void **)args);
}
