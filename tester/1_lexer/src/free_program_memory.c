/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_program_memory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:33:39 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 19:00:08 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static void	free_list(void **list);

void	free_program_memory(t_data *data)
{
	if (data->valgrind_path)
		free(data->valgrind_path);
	if (data->paths)
		free_list((void **)data->paths);
	if (data->process.pid)
		free(data->process.pid);
	if (data->process.status)
		free(data->process.status);
	if (data->input_tests_fd)
		free(data->input_tests_fd);
	if (data->expected_outputs_fd)
		free(data->expected_outputs_fd);
	if (data->user_outputs_fd)
		free(data->user_outputs_fd);
	if (data->user_error_fd)
		free(data->user_error_fd);
	if (data->input_tests_name)
		free_list((void **)data->input_tests_name);
	if (data->expected_outputs_name)
		free_list((void **)data->expected_outputs_name);
	if (data->user_outputs_name)
		free_list((void **)data->user_outputs_name);
	if (data->user_error_name)
		free_list((void **)data->user_error_name);
}

static void	free_list(void **list)
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
