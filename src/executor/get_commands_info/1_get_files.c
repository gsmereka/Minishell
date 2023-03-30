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

static void		init_fds(int *fds, int amount);
static int		count_files(t_token *token);
static void		get_files_details(t_token *token, t_cmd *cmd);
static t_token	*format_file(t_token *token, int file, int mode, t_cmd *cmd);

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

// FILES MODES
// 0 = Normal input '<'
// 1 = Heredoc '<<'
// 2 - Normal output '>'
// 3 - Append Output '>>'

static void	get_files_details(t_token *token, t_cmd *cmd)
{
	int	file;

	file = 0;
	while (token)
	{
		if (is_reserved("<", token))
		{
			format_file(token, file, 0, cmd);
			file++;
		}
		else if (is_reserved("<<", token))
		{
			format_file(token, file, 1, cmd);
			file++;
		}
		else if (is_reserved(">", token))
		{
			format_file(token, file, 2, cmd);
			file++;
		}
		else if (is_reserved(">>", token))
		{
			format_file(token, file, 3, cmd);
			file++;
		}
		else if (is_reserved("|", token))
			break ;
		token = token->next;
	}
}

static t_token	*format_file(t_token *token, int file, int mode, t_cmd *cmd)
{
	cmd->files[file] = ft_strdup(token->next->content);
	cmd->files_modes[file] = mode;
	return (token);
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
		else if (is_reserved(">", token))
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
