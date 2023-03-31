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

static void		init_fds(int *fds, int files_amount);
static int		count_files(t_token *token);
static void		get_files_details(t_token *token, t_cmd *cmd);
static int		format_file(t_token *token, int file, t_cmd *cmd);

void	get_files(t_token *token, t_cmd *cmd)
{
	int	files_amount;

	files_amount = count_files(token);
	if (!files_amount)
		return ;
	cmd->files = ft_calloc(files_amount + 1, sizeof (char *));
	cmd->files_fd = ft_calloc(files_amount + 1, sizeof (int));
	init_fds(cmd->files_fd, files_amount);
	cmd->files_modes = ft_calloc(files_amount + 1, sizeof (int));
	if (!cmd->files || !cmd->files_modes || !cmd->files_fd)
		return ;
	get_files_details(token, cmd);
}

static void	get_files_details(t_token *token, t_cmd *cmd)
{
	int	file;

	file = 0;
	while (token)
	{
		if (format_file(token, file, cmd))
			file++;
		else if (is_reserved("|", token))
			break ;
		token = token->next;
	}
}

// FILES MODES
// 0 = Normal input '<'
// 1 = Heredoc '<<'
// 2 - Normal output '>'
// 3 - Append Output '>>'

static int	format_file(t_token *token, int file, t_cmd *cmd)
{
	if (is_reserved("<", token))
	{
		cmd->files[file] = ft_strdup(token->next->content);
		cmd->files_modes[file] = 0;
	}
	else if (is_reserved("<<", token))
	{
		cmd->files[file] = ft_strdup(token->next->content);
		cmd->files_modes[file] = 1;
	}
	else if (is_reserved(">", token))
	{
		cmd->files[file] = ft_strdup(token->next->content);
		cmd->files_modes[file] = 2;
	}
	else if (is_reserved(">>", token))
	{
		cmd->files[file] = ft_strdup(token->next->content);
		cmd->files_modes[file] = 3;
	}
	else
		return (0);
	return (1);
}

static int	count_files(t_token *token)
{
	int	files_amount;

	files_amount = 0;
	while (token)
	{
		if (is_reserved("<", token))
			files_amount++;
		else if (is_reserved("<<", token))
			files_amount++;
		else if (is_reserved(">", token))
			files_amount++;
		else if (is_reserved(">>", token))
			files_amount++;
		else if (is_reserved("|", token))
			break ;
		token = token->next;
	}
	return (files_amount);
}

static void	init_fds(int *fds, int files_amount)
{
	int	i;

	i = 0;
	if (!fds)
		return ;
	while (i < files_amount)
	{
		fds[i] = -1;
		i++;
	}
}
