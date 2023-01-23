/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:16:42 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/22 23:26:20 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static void free_list(void **list)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (list[i])
			free(list[i]);
		i++;
	}
	free (list);
}

static void	free_program_memory(t_data *data)
{
	if (data->input_tests_fd)
		free(data->input_tests_fd);
	if (data->input_tests_name)
		free_list((void **)data->input_tests_name);
}

void	finalize(t_data *data)
{
	free_program_memory(data);
	exit(0);
}

void	exit_error(int error, char *msg, t_data *data)
{
	write(2, msg, strlen(msg));
	free_program_memory(data);
	exit(error);
}
