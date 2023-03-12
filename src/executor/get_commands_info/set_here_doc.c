/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_here_doc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:05:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/12 14:28:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

static void	init_heredoc_pipe(t_cmd *cmd, int fd_index, t_data *data);
static void	set_here_doc_content(t_cmd *cmd, int fd_index, t_data *data);
static int	compare_input_with_limiter(char *input, char *limiter, t_data *data);
static int	need_interrupt(char *str, char *limiter);
static char	*ft_strjoin_with_free(char *s1, char *s2);

void	set_here_doc(t_data *data)
{
	t_cmd	**cmd;
	int 	cmd_index;
	int		fd_index;

	cmd_index = 0;
	cmd = data->exec->cmds;
	while (cmd_index < data->exec->cmds_amount)
	{
		if (cmd[cmd_index]->infiles)
		{
			fd_index = 0;
			while (cmd[cmd_index]->infiles[fd_index])
			{
				init_heredoc_pipe(cmd[cmd_index], fd_index, data);
				if (cmd[cmd_index]->inputs_modes[fd_index] == 1)
					set_here_doc_content(cmd[cmd_index], fd_index, data);
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
		exit_error(12, "Fail allocating memory for here_doc", data);
	pipe(heredoc_pipe);
}

static void	set_here_doc_content(t_cmd *cmd, int fd_index, t_data *data)
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
		write(2, "Error at simulate here_doc", ft_strlen("Error at simulate here_doc"));
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
	msg = ft_strdup("bash: warning: here-document at line "\
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

static char	*ft_strjoin_with_free(char *s1, char *s2)
{
	char	*new_s;
	int		s1_size;
	int		s2_size;
	int		i;

	if (!s1)
		s1 = ft_strdup("");
	if (!s1 | !s2)
		return (NULL);
	i = 0;
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	new_s = (char *)malloc((s1_size + s2_size + 1) * sizeof(char));
	if (new_s == NULL)
		return (NULL);
	while (i < (s1_size + s2_size + 1))
	{
		if (i < s1_size)
			new_s[i] = s1[i];
		else
			new_s[i] = s2[i - s1_size];
		i++;
	}
	free(s1);
	return ((char *)new_s);
}
