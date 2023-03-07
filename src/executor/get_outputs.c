/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:12:36 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/07 18:41:09 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static int	count_outputs(t_token *token);
static void	get_outputs_details(t_token *token, t_cmd *cmd);

void	get_outputs(t_token *token, t_cmd *cmd, t_data *data)
{
	int	outputs_amount;

	outputs_amount = count_outputs(token);
	if (!outputs_amount)
		return ;
	cmd->outfiles = ft_calloc(outputs_amount + 1, sizeof (char *));
	cmd->outputs_modes = ft_calloc(outputs_amount + 1, sizeof (int));
	get_outputs_details(token, cmd);
}

// DICIONARIO DE outPUT MODES
// 0 = Normal output '<'
// 1s = here doc '<<'

static void	get_outputs_details(t_token *token, t_cmd *cmd)
{
	int	output;

	output = 0;
	while (token)
	{
		if (ft_strncmp(token->content, "<", ft_strlen(token->content)) == 0)
		{
			cmd->outfiles[output] = ft_strdup(token->next->content);
			cmd->outputs_modes[output] = 0;
			output++;
		}
		else if (ft_strncmp(token->content,
				"<<", ft_strlen(token->content)) == 0)
		{
			cmd->outfiles[output] = ft_strdup(token->next->content);
			cmd->outputs_modes[output] = 1;
			output++;
		}
		else if (ft_strncmp(token->content,
				"|", ft_strlen(token->content)) == 0)
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
