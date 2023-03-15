/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_heredoc_pipes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:05:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 21:44:59 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../headers/minishell.h"

static void	init_heredoc_pipe(t_cmd *cmd, int fd_index, t_data *data);
static void	set_heredoc_content(t_cmd *cmd, int fd_index, t_data *data);
static int	compare_input_with_limiter(char *input, char *limiter, t_data *data);
static int	need_interrupt(char *str, char *limiter);

void	set_heredoc(t_data *data)
{
	t_cmd	**cmd;
	int 	cmd_index;
	int		fd_index;

	cmd_index = 0;
	cmd = data->exec->cmds;
	heredoc_signals_handling(data);
	while (cmd_index < data->exec->cmds_amount)
	{
		if (cmd[cmd_index]->infiles)
		{
			fd_index = 0;
			while (cmd[cmd_index]->infiles[fd_index])
			{
				init_heredoc_pipe(cmd[cmd_index], fd_index, data);
				if (cmd[cmd_index]->inputs_modes[fd_index] == 1)
					set_heredoc_content(cmd[cmd_index], fd_index, data);
				fd_index++;
			}
		}
		cmd_index++;
	}
}

static void	init_heredoc_pipe(t_cmd *cmd, int fd_index, t_data *data)
{
	int	*heredoc_pipe;

	cmd->heredocs_pipes[fd_index] = ft_calloc(2, sizeof(int));
	heredoc_pipe = cmd->heredocs_pipes[fd_index];
	if (!heredoc_pipe)
		exit_error(12, "Fail allocating memory for heredoc", data);
	pipe(heredoc_pipe);
}

static void	set_heredoc_content(t_cmd *cmd, int fd_index, t_data *data)
{
	int		*heredoc_pipe;
	char	*input;
	char	*limiter;
	int		i;

	i = 0;
	input = NULL;
	limiter = cmd->infiles[fd_index];
	heredoc_pipe = cmd->heredocs_pipes[fd_index];
	while (i >= 0)
	{
		write(1, "> ", 2);
		input = get_next_line_with_free(0, 0);
		if (need_interrupt(input, limiter))
			break ;
		if (compare_input_with_limiter(input, limiter, data))
			break ;
		write(heredoc_pipe[1], input, ft_strlen(input));
		free(input);
		i++;
	}
	get_next_line_with_free(0, 1);
	close(heredoc_pipe[1]);
}

static int	compare_input_with_limiter(char *input, char *limiter, t_data *data)
{
	int		diff;
	int		size;
	char	*limiter_with_new_line;

	limiter_with_new_line = ft_strjoin(limiter, "\n");
	if (!limiter_with_new_line)
	{
		free(input);
		write(2, "Error at simulate heredoc", ft_strlen("Error at simulate heredoc"));
		// definir erro 12
		return (1);
	}
	size = ft_strlen(limiter_with_new_line);
	diff = ft_strncmp(input, limiter_with_new_line, size + 1);
	free(limiter_with_new_line);
	if (diff != 0)
		return (0);
	free(input);
	return (1);
}

static int	need_interrupt(char *input, char *limiter)
{
	char	*msg;

	if (input != NULL)
		return (0);
	msg = ft_strdup("\nbash: warning: here-document "\
		"delimited by end-of-file (wanted `");
	msg = ft_strjoin_with_free(msg, limiter);
	msg = ft_strjoin_with_free(msg, "')\n");
	if (msg != NULL)
	{
		write(2, msg, ft_strlen(msg));
		free(msg);
	}
	return (1);
}
