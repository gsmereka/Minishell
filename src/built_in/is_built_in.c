/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:37:49 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/10 16:39:09 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_built_in(t_cmd *cmd)
{
	char	**args;

	args = cmd->args;
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
