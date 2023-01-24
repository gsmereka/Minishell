/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:16:42 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/23 21:52:15 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static int	close_files(t_data *data);

static void free_list(void **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (list[i])
			free(list[i]);
		i++;
	}
	free (list);
}

void	wait_tests(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->input_tests_amount)
	{
		waitpid(data->process.pid[i], &data->process.status[i], WUNTRACED);
		i++;
	}
}

static void	free_program_memory(t_data *data)
{
	if (data->input_tests_fd)
		free(data->input_tests_fd);
	if (data->expected_outputs_fd)
		free(data->expected_outputs_fd);
	if (data->user_outputs_fd)
		free(data->user_outputs_fd);
	if (data->input_tests_name)
		free_list((void **)data->input_tests_name);
	if (data->expected_outputs_name)
		free_list((void **)data->expected_outputs_name);
	if (data->user_outputs_name)
		free_list((void **)data->user_outputs_name);
}

void	finalize(t_data *data)
{
	close_files(data);
	free_program_memory(data);
	exit(0);
}

void	exit_error(int error, char *msg, t_data *data)
{
	close_files(data);
	write(2, msg, strlen(msg));
	free_program_memory(data);
	exit(error);
}

static int	close_files(t_data *data)
{
	int i;

	if (!data->input_tests_fd || !data->expected_outputs_fd || !data->user_outputs_fd)
		return (-1);
	i = 0;
	while (i < data->input_tests_amount)
	{
		if (data->input_tests_fd[i])
			close(data->input_tests_fd[i]);
		if (data->expected_outputs_fd[i])
			close(data->expected_outputs_fd[i]);
		if (data->user_outputs_fd[i])
			close(data->user_outputs_fd[i]);
		i++;
	}
	return (0);
}