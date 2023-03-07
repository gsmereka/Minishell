/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:29:33 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/07 14:15:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	set_input_exec_info(t_data *data);
static int	count_cmds(t_data *data);
static void	split_cmd_tokens(t_data *data);

void	get_commands_info(t_data *data)
{
	set_input_exec_info(data);
	split_cmd_tokens(data);
}

static void	split_cmd_tokens(t_data *data)
{
	t_token	*token;
	t_cmd	**cmd;
	int		cmd_index;

	cmd_index = 0;
	token = data->tokens;
	cmd = data->exec->cmds;
	while (token)
	{
		token = format_cmd(token, cmd[cmd_index], data);
		cmd_index++;
	}
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

static void	set_input_exec_info(t_data *data)
{
	data->exec = ft_calloc(1, sizeof(t_exec));
	data->exec->cmds_amount = count_cmds(data);
	data->exec->cmds = ft_calloc(data->exec->cmds_amount + 1, sizeof(t_cmd));
	data->exec->pipes = ft_calloc(data->exec->cmds_amount + 1, sizeof(int *));
}
