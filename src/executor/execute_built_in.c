/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_built_in.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:46:14 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	execute_built_in(t_cmd *cmd, t_data *g_data)
{
	char	**args;

	args = cmd->args;
	if (!args || !args[0])
		return ;
	else if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		ft_echo(args, g_data);
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		ft_cd(args, g_data);
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		ft_env(args, g_data);
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		ft_exit(args, g_data);
	else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		ft_pwd(args, g_data);
	else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		ft_export(args, g_data);
	else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		ft_unset(args, g_data);
}
