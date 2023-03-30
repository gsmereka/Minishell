/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_format_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:11:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/30 13:16:43 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static t_token	*find_actual_command(t_token *token);
static void		set_cmd_composition(t_token *token, t_cmd *cmd);
static void		set_cmd_args_composition(int args_size,
					t_token *token, t_cmd *cmd);
static int		count_args(t_token *token);

void	format_cmd(t_token *token, t_cmd *cmd)
{
	t_token	*cmd_token;

	get_files(token, cmd);
	cmd_token = find_actual_command(token);
	set_cmd_composition(cmd_token, cmd);
}

static void	set_cmd_composition(t_token *token, t_cmd *cmd)
{
	int	args_amount;
	int	index;

	args_amount = count_args(token);
	if (!args_amount)
		return ;
	cmd->name = ft_strdup(token->content);
	cmd->args = ft_calloc(args_amount + 1, sizeof(char *));
	if (!cmd->name || !cmd->args)
		return ;
	set_cmd_args_composition(args_amount, token, cmd);
}

static void	set_cmd_args_composition(int args_size, t_token *token, t_cmd *cmd)
{
	int	index;

	index = 0;
	while (index < args_size)
	{
		if (is_reserved("<", token))
			token = token->next;
		else if (is_reserved("<<", token))
			token = token->next;
		else if (is_reserved(">", token))
			token = token->next;
		else if (is_reserved(">>", token))
			token = token->next;
		else
		{
			cmd->args[index] = ft_strdup(token->content);
			index++;
		}
		token = token->next;
	}
}

static int	count_args(t_token *token)
{
	int	args_amount;

	args_amount = 0;
	while (token)
	{
		if (is_reserved("<", token))
			token = token->next;
		else if (is_reserved("<<", token))
			token = token->next;
		else if (is_reserved(">", token))
			token = token->next;
		else if (is_reserved(">>", token))
			token = token->next;
		else if (is_reserved("|", token))
			token = token->next;
		else
			args_amount++;
		token = token->next;
	}
	return (args_amount);
}

static t_token	*find_actual_command(t_token *token)
{
	while (token)
	{
		if (is_reserved("<", token))
			token = token->next->next;
		else if (is_reserved("<<", token))
			token = token->next->next;
		else if (is_reserved(">", token))
			return (NULL);
		else if (is_reserved(">>", token))
			return (NULL);
		else if (is_reserved("|", token))
			return (NULL);
		else
			break ;
	}
	return (token);
}
