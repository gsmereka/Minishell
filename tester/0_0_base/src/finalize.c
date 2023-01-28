/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:16:42 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/27 22:38:26 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static int	close_files(t_data *data);
static void	close_std_fds(t_data *data);

void	finalize(t_data *data)
{
	close_files(data);
	free_program_memory(data);
	exit(0);
}

void	exit_error(int error, char *msg, t_data *data)
{
	write(2, msg, strlen(msg));
	free_program_memory(data);
	exit(error);
}

static int	close_files(t_data *data)
{
	int	i;

	if (!data->input_tests_fd || !data->expected_outputs_fd
		|| !data->user_outputs_fd || !data->user_error_fd)
		return (-1);
	i = 0;
	close_std_fds(data);
	while (i < data->input_tests_amount)
	{
		if (data->input_tests_fd[i] >= 0)
			close(data->input_tests_fd[i]);
		if (data->expected_outputs_fd[i] >= 0)
			close(data->expected_outputs_fd[i]);
		if (data->user_outputs_fd[i] >= 0)
			close(data->user_outputs_fd[i]);
		if (data->user_error_fd[i] >= 0)
			close(data->user_error_fd[i]);
		i++;
	}
	return (0);
}

static void	close_std_fds(t_data *data)
{
	close(0);
	close(1);
	close(2);
	if (data->original_stdin >= 0)
		close(data->original_stdin);
	if (data->original_stdout >= 0)
		close(data->original_stdout);
	if (data->original_stder >= 0)
		close(data->original_stder);
}
