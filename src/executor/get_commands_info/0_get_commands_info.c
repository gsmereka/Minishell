/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_get_commands_info.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:29:33 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/03 17:27:26 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static t_token	*find_next_command(t_token *token);
static int		count_cmds(t_data *data);
static int		init_execution_structure(t_data *data);
static void		set_cmd_tokens(t_data *data);

int	get_commands_info(t_data *data)
{
	if (!init_execution_structure(data))
	{
		att_exit_status(12, data);
		return (0);
	}
	set_cmd_tokens(data);
	if (!get_env_paths(data))
		return (0);
	set_cmds_paths(data);
	return (1);
}

static int	init_execution_structure(t_data *data)
{
	int	i;

	data->exec = ft_calloc(1, sizeof(t_exec));
	if (!data->exec)
		return (0);
	data->exec->cmds_amount = count_cmds(data);
	data->exec->cmds = ft_calloc(data->exec->cmds_amount + 1, sizeof(t_cmd));
	data->exec->pipes = ft_calloc(data->exec->cmds_amount + 1, sizeof(int *));
	data->exec->pid = ft_calloc(data->exec->cmds_amount + 1, sizeof(int));
	data->exec->status = ft_calloc(data->exec->cmds_amount + 1, sizeof(int));
	if (!data->exec->cmds || !data->exec->pipes || !data->exec->pid
		|| !data->exec->status)
		return (0);
	i = 0;
	while (i < data->exec->cmds_amount)
	{
		data->exec->pipes[i] = ft_calloc(2, sizeof(int));
		if (!data->exec->pipes[i])
			return (0);
		i++;
	}
	return (1);
}

static int	count_cmds(t_data *data)
{
	t_token	*token;
	int		size;

	size = 1;
	token = data->tokens;
	while (token)
	{
		if (is_reserved("|", token))
			size++;
		token = token->next;
	}
	return (size);
}

static void	set_cmd_tokens(t_data *data)
{
	t_token	*token;
	t_cmd	**cmd;
	int		cmd_index;

	cmd_index = 0;
	token = data->tokens;
	cmd = data->exec->cmds;
	while (token)
	{
		cmd[cmd_index] = ft_calloc(1, sizeof(t_cmd));
		format_cmd(token, cmd[cmd_index]);
		token = find_next_command(token);
		cmd_index++;
	}
}

static t_token	*find_next_command(t_token *token)
{
	while (token)
	{
		if (is_reserved("|", token))
		{
			return (token->next);
		}
		token = token->next;
	}
	return (token);
}
