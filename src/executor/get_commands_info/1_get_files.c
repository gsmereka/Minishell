/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_get_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:12:05 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/30 12:23:39 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	init_fds(int *fds, int amount);
static int	count_files(t_token *token);
static void	get_files_details(t_token *token, t_cmd *cmd);

void	get_files(t_token *token, t_cmd *cmd)
{
	int	files_amount;

	files_amount = count_files(token);
	if (!files_amount)
		return ;
	cmd->infiles = ft_calloc(files_amount + 1, sizeof (char *));
	cmd->infiles_fd = ft_calloc(files_amount + 1, sizeof (int));
	init_fds(cmd->infiles_fd, files_amount);
	cmd->files_modes = ft_calloc(files_amount + 1, sizeof (int));
	get_files_details(token, cmd);
}

// INPUT MODES
// 0 = Normal input '<'
// 1 = Heredoc '<<'

static void	get_files_details(t_token *token, t_cmd *cmd)
{
	int	input;

	input = 0;
	if (!cmd->infiles || !cmd->files_modes)
		return ;
	while (token)
	{
		if (is_reserved("<", token))
		{
			cmd->infiles[input] = ft_strdup(token->next->content);
			cmd->files_modes[input] = 0;
			input++;
		}
		else if (is_reserved("<<", token))
		{
			cmd->infiles[input] = ft_strdup(token->next->content);
			cmd->files_modes[input] = 1;
			input++;
		}
		else if (is_reserved("|", token))
			break ;
		token = token->next;
	}
}

static int	count_files(t_token *token)
{
	int	size;

	size = 0;
	while (token)
	{
		if (is_reserved("<", token))
			size++;
		else if (is_reserved("<<", token))
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
