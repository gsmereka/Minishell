/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:29:33 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/07 19:59:46 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	get_execution_info(t_data *data);
static int	count_cmds(t_data *data);

void	get_commands_info(t_data *data)
{
	data->exec = ft_calloc(1, sizeof(t_exec));
	data->exec->cmds_amount = count_cmds(data);
	data->exec->cmds = ft_calloc(data->exec->cmds_amount + 1, sizeof(t_cmd));
	data->exec->pipes = ft_calloc(data->exec->cmds_amount + 1, sizeof(int *));
}

static int	count_cmds(t_data *data)
{
	t_token	*token;
	int		size;

	size = 0;
	token = data->tokens;
	while (token)
	{
		if (ft_strncmp(token->content, "|", ft_strlen(token->content)) == 0)
		{
			// if (reserved_word(token))
				size++;
		}
		token = token->next;
	}
	return (size);
}
