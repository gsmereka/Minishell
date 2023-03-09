/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/09 12:03:50 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	is_only_one_built_in(t_data *data);

void	init_executor(t_data *data)
{
	if (!data->tokens)
		return ;
	get_commands_info(data);
	if (!data->exec)
		return ;
	if (is_only_one_built_in(data))
		execute_built_in(0, data);
	else
		set_processes(data);
}

static int	is_only_one_built_in(t_data *data)
{
	char	**args;

	if (data->exec->cmds_amount > 1)
		return (0);
	args = data->exec->cmds[0]->args;
	if (!args || !args[0])
		return (0);
	else if (ft_strncmp(args[0], "echo", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "cd", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "env", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "exit", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "pwd", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "export", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(args[0], "unset", ft_strlen(args[0])) == 0)
		return (1);
	return (0);
}
