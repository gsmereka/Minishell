/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:16:42 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static int	close_files(t_data *g_data);
static void	close_std_fds(t_data *g_data);

void	finalize(t_data *g_data)
{
	close_files(g_data);
	free_program_memory(g_data);
	exit(0);
}

void	exit_error(int error, char *msg, t_data *g_data)
{
	write(2, msg, strlen(msg));
	free_program_memory(g_data);
	exit(error);
}

static int	close_files(t_data *g_data)
{
	int	i;

	if (!g_data->input_tests_fd || !g_data->expected_outputs_fd
		|| !g_data->user_outputs_fd || !g_data->user_error_fd)
		return (-1);
	i = 0;
	close_std_fds(g_data);
	while (i < g_data->input_tests_amount)
	{
		if (g_data->input_tests_fd[i] >= 0)
			close(g_data->input_tests_fd[i]);
		if (g_data->expected_outputs_fd[i] >= 0)
			close(g_data->expected_outputs_fd[i]);
		if (g_data->user_outputs_fd[i] >= 0)
			close(g_data->user_outputs_fd[i]);
		if (g_data->user_error_fd[i] >= 0)
			close(g_data->user_error_fd[i]);
		i++;
	}
	return (0);
}

static void	close_std_fds(t_data *g_data)
{
	close(0);
	close(1);
	close(2);
	if (g_data->original_stdin >= 0)
		close(g_data->original_stdin);
	if (g_data->original_stdout >= 0)
		close(g_data->original_stdout);
	if (g_data->original_stder >= 0)
		close(g_data->original_stder);
}
