/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:46:14 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/13 13:18:03 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	execute_built_in(t_cmd *cmd, t_data *data)
{
	char	**args;

	args = cmd->args;
	if (!args || !args[0])
		return ;
	if (ft_strcmp(args[0], "exit") != 0)
		att_exit_status(0, data);
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(args, data);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args, data);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(args, data);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args, data);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(args, data);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(args, data);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, data);
}
