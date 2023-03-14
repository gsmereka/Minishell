/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_program_memory.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 22:33:39 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static void	free_list(void **list);

void	free_program_memory(t_data *g_data)
{
	if (g_data->valgrind_path)
		free(g_data->valgrind_path);
	if (g_data->paths)
		free_list((void **)g_data->paths);
	if (g_data->process.pid)
		free(g_data->process.pid);
	if (g_data->process.status)
		free(g_data->process.status);
	if (g_data->input_tests_fd)
		free(g_data->input_tests_fd);
	if (g_data->expected_outputs_fd)
		free(g_data->expected_outputs_fd);
	if (g_data->user_outputs_fd)
		free(g_data->user_outputs_fd);
	if (g_data->user_error_fd)
		free(g_data->user_error_fd);
	if (g_data->input_tests_name)
		free_list((void **)g_data->input_tests_name);
	if (g_data->expected_outputs_name)
		free_list((void **)g_data->expected_outputs_name);
	if (g_data->user_outputs_name)
		free_list((void **)g_data->user_outputs_name);
	if (g_data->user_error_name)
		free_list((void **)g_data->user_error_name);
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
