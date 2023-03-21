/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_cmd_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 20:50:23 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/20 21:20:10 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static int	heredoc_infiles_loop(t_cmd *cmd, t_data *data);
static void	init_heredoc_pipe(t_cmd *cmd, int fd_index, t_data *data);
static int	set_heredoc_content(t_cmd *cmd, int fd_index, t_data *data);
static int	compare_input_with_limiter(char *input,
				char *limiter, t_data *data);

int	heredoc_cmd_loop(t_data *data)
{
	t_cmd	**cmd;
	int		cmd_index;
	int		fd_index;

	cmd_index = 0;
	cmd = data->exec->cmds;
	while (cmd_index < data->exec->cmds_amount)
	{
		if (!heredoc_infiles_loop(cmd[cmd_index], data))
			return (0);
		cmd_index++;
	}
	return (1);
}

static int	heredoc_infiles_loop(t_cmd *cmd, t_data *data)
{
	int	fd_index;

	fd_index = 0;
	if (!cmd->infiles)
		return (1);
	while (cmd->infiles[fd_index])
	{
		init_heredoc_pipe(cmd, fd_index, data);
		if (cmd->inputs_modes[fd_index] == 1 && cmd->heredocs_pipes)
		{
			if (!set_heredoc_content(cmd, fd_index, data))
				return (0);
		}
		fd_index++;
	}
	return (1);
}

static void	init_heredoc_pipe(t_cmd *cmd, int fd_index, t_data *data)
{
	int	*heredoc_pipe;

	if (!cmd->heredocs_pipes)
		return ;
	cmd->heredocs_pipes[fd_index] = ft_calloc(2, sizeof(int));
	heredoc_pipe = cmd->heredocs_pipes[fd_index];
	if (!heredoc_pipe)
		exit_error(12, "Fail allocating memory for heredoc", data);
	pipe(heredoc_pipe);
}

static int	set_heredoc_content(t_cmd *cmd, int fd_index, t_data *data)
{
	int		*heredoc_pipe;
	char	*input;
	char	*limiter;

	limiter = cmd->infiles[fd_index];
	heredoc_pipe = cmd->heredocs_pipes[fd_index];
	while (cmd)
	{
		write(1, "> ", 2);
		input = get_next_line_with_free(0, 0);
		if (data->exec->need_interrupt)
		{
			free(input);
			return (0);
		}
		if (heredoc_interrupt(input, limiter, data))
			break ;
		if (compare_input_with_limiter(input, limiter, data))
			break ;
		write(heredoc_pipe[1], input, ft_strlen(input));
		free(input);
	}
	get_next_line_with_free(0, 1);
	close(heredoc_pipe[1]);
	return (1);
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
