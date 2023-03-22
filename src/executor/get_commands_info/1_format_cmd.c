/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_format_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:11:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/22 11:49:36 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static t_token	*find_actual_command(t_token *token);
static void		set_cmd_composition(t_token *token, t_cmd *cmd);
static int		count_args(t_token *token);

void	format_cmd(t_token *token, t_cmd *cmd, t_data *data)
{
	t_token	*cmd_token;

	cmd_token = find_actual_command(token);
	set_cmd_composition(cmd_token, cmd);
	get_inputs(token, cmd, data);
	get_outputs(token, cmd, data);
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
	index = 0;
	while (index < args_amount)
	{
		cmd->args[index] = ft_strdup(token->content);
		token = token->next;
		index++;
	}
}

static int	count_args(t_token *token)
{
	int	args_amount;

	args_amount = 0;
	while (token)
	{
		if (is_reserved("<", token))
			break ;
		else if (is_reserved("<<", token))
			break ;
		else if (is_reserved(">", token))
			break ;
		else if (is_reserved(">>", token))
			break ;
		else if (is_reserved("|", token))
			break ;
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
