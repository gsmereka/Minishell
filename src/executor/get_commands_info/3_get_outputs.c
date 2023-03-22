/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_get_outputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:12:36 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/22 17:40:17 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	init_fds(int *fds, int amount);
static int	count_outputs(t_token *token);
static void	get_outputs_details(t_token *token, t_cmd *cmd);

void	get_outputs(t_token *token, t_cmd *cmd)
{
	int	outputs_amount;

	outputs_amount = count_outputs(token);
	if (!outputs_amount)
		return ;
	cmd->outfiles = ft_calloc(outputs_amount + 1, sizeof (char *));
	cmd->outfiles_fd = ft_calloc(outputs_amount + 1, sizeof (int));
	init_fds(cmd->outfiles_fd, outputs_amount);
	cmd->outputs_modes = ft_calloc(outputs_amount + 1, sizeof (int));
	get_outputs_details(token, cmd);
}

// OUTPUT MODES
// 0 = Normal output '>'
// 1 = Append mode '>>'

static void	get_outputs_details(t_token *token, t_cmd *cmd)
{
	int	output;

	output = 0;
	if (!cmd->outfiles || !cmd->outputs_modes)
		return ;
	while (token)
	{
		if (is_reserved(">", token))
		{
			cmd->outfiles[output] = ft_strdup(token->next->content);
			cmd->outputs_modes[output] = 0;
			output++;
		}
		else if (is_reserved(">>", token))
		{
			cmd->outfiles[output] = ft_strdup(token->next->content);
			cmd->outputs_modes[output] = 1;
			output++;
		}
		else if (is_reserved("|", token))
			break ;
		token = token->next;
	}
}

static int	count_outputs(t_token *token)
{
	int	size;

	size = 0;
	while (token)
	{
		if (is_reserved(">", token))
			size++;
		else if (is_reserved(">>", token))
			size++;
		else if (is_reserved("|", token))
			break ;
		token = token->next;
	}
	return (size);
}

static void	init_fds(int *fds, int amount)
{
	int	i;

	i = 0;
	if (!fds)
		return ;
	while (i < amount)
	{
		fds[i] = -1;
		i++;
	}
}
