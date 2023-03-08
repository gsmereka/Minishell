/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_inputs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:12:05 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/08 10:02:58 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	count_inputs(t_token *token);
static void	get_inputs_details(t_token *token, t_cmd *cmd);

void	get_inputs(t_token *token, t_cmd *cmd, t_data *data)
{
	int	inputs_amount;

	inputs_amount = count_inputs(token);
	if (!inputs_amount)
		return ;
	cmd->infiles = ft_calloc(inputs_amount + 1, sizeof (char *));
	cmd->inputs_modes = ft_calloc(inputs_amount + 1, sizeof (int));
	get_inputs_details(token, cmd);
}

// DICIONARIO DE INPUT MODES
// 0 = Normal input '<'
// 1 = here doc '<<'

static void	get_inputs_details(t_token *token, t_cmd *cmd)
{
	int	input;

	input = 0;
	while (token)
	{
		if (ft_strncmp(token->content, "<", ft_strlen(token->content)) == 0)
		{
			cmd->infiles[input] = ft_strdup(token->next->content);
			cmd->inputs_modes[input] = 0;
			input++;
		}
		else if (ft_strncmp(token->content,
				"<<", ft_strlen(token->content)) == 0)
		{
			cmd->infiles[input] = ft_strdup(token->next->content);
			cmd->inputs_modes[input] = 1;
			input++;
		}
		else if (ft_strncmp(token->content,
				"|", ft_strlen(token->content)) == 0)
			break ;
		token = token->next;
	}
}

static int	count_inputs(t_token *token)
{
	int	size;

	size = 0;
	while (token)
	{
		if (ft_strncmp(token->content, "<", ft_strlen(token->content)) == 0)
			size++;
		else if (ft_strncmp(token->content,
				"<<", ft_strlen(token->content)) == 0)
			size++;
		else if (ft_strncmp(token->content,
				"|", ft_strlen(token->content)) == 0)
			break ;
		token = token->next;
	}
	return (size);
}
