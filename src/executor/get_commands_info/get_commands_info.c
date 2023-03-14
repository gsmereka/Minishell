/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands_info.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 13:29:33 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static t_token	*find_next_command(t_token *token);
static int		count_cmds(t_data *g_data);
static void		init_execution_structure(t_data *g_data);
static void		set_cmd_tokens(t_data *g_data);

void	get_commands_info(t_data *g_data)
{
	init_execution_structure(g_data);
	set_cmd_tokens(g_data);
	get_env_paths(g_data);
	set_cmds_paths(g_data);
}

static void	init_execution_structure(t_data *g_data)
{
	int	i;

	g_data->exec = ft_calloc(1, sizeof(t_exec));
	g_data->exec->cmds_amount = count_cmds(g_data);
	g_data->exec->cmds = ft_calloc(g_data->exec->cmds_amount + 1, sizeof(t_cmd));
	g_data->exec->pipes = ft_calloc(g_data->exec->cmds_amount + 1, sizeof(int *));
	i = 0;
	while (i < g_data->exec->cmds_amount)
	{
		g_data->exec->pipes[i] = ft_calloc(2, sizeof(int));
		i++;
	}
}

static int	count_cmds(t_data *g_data)
{
	t_token	*token;
	int		size;

	size = 1;
	token = g_data->tokens;
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

static void	set_cmd_tokens(t_data *g_data)
{
	t_token	*token;
	t_cmd	**cmd;
	int		cmd_index;

	cmd_index = 0;
	token = g_data->tokens;
	cmd = g_data->exec->cmds;
	while (token)
	{
		cmd[cmd_index] = ft_calloc(1, sizeof(t_cmd));
		format_cmd(token, cmd[cmd_index], g_data);
		token = find_next_command(token);
		cmd_index++;
	}
}

static t_token	*find_next_command(t_token *token)
{
	while (token)
	{
		if (ft_strncmp(token->content, "|", ft_strlen(token->content)) == 0)
		{
			return(token->next);
		}
		token = token->next;
	}
	return (token);
}
