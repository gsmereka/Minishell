/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_format_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:11:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/01 22:35:53 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void		set_cmd_composition(t_token *token, t_cmd *cmd);
static void		set_cmd_args_composition(int args_size,
					t_token *token, t_cmd *cmd);
static int		count_args(t_token *token);

void	format_cmd(t_token *token, t_cmd *cmd)
{
	set_cmd_composition(token, cmd);
	get_files(token, cmd);
}

static void	set_cmd_composition(t_token *token, t_cmd *cmd)
{
	int	args_amount;
	int	index;

	args_amount = count_args(token);
	if (!args_amount)
		return ;
	cmd->args = ft_calloc(args_amount + 1, sizeof(char *));
	if (!cmd->args)
		return ;
	set_cmd_args_composition(args_amount, token, cmd);
	if (cmd->args && cmd->args[0])
		cmd->name = ft_strdup(cmd->args[0]);
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
		else if (is_reserved("|", token))
			break ;
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
