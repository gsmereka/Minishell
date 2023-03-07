/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:11:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/07 14:47:53 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

//  < arquivo_1 > arquivo_2 ---- Podem existir Comandos Que não existem.
static int	find_the_command(t_token *token);

void	format_cmd(t_token *token, t_cmd *cmd, t_data *data)
{
	int	cmd_token;

	cmd_token = find_the_command(token);
	// check_inputs(token, cmd, data);
	// check_outputs(token, cmd, data);
}

static int	find_the_command(t_token *token)
{
	int	cmd_token;

	cmd_token = 0;
	while (token)
	{
		if (ft_strncmp(token->content, "<", ft_strlen(token->content)) == 0)
		{
			token = token->next->next;
			cmd_token += 2;
		}
		else if (ft_strncmp(token->content, "<<", ft_strlen(token->content)) == 0)
		{
			token = token->next->next;
			cmd_token += 2;
		}
		else if (ft_strncmp(token->content, ">", ft_strlen(token->content)) == 0)
		{
			cmd_token == -1;
			break ;
		}
		else if (ft_strncmp(token->content, ">>", ft_strlen(token->content)) == 0)
		{
			cmd_token == -1;
			break ;
		}
		else if (ft_strncmp(token->content, "|", ft_strlen(token->content)) == 0)
		{
			cmd_token == -1;
			break ;
		}
		else
			break ;
	}	
}