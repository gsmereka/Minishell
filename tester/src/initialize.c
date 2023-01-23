/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 23:10:37 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/22 23:16:39 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

void	initialize(t_data *data)
{
	data->input_tests_amount = 3;
	data->input_tests_fd = calloc(data->input_tests_amount + 1, sizeof(int));
	data->input_tests_name = calloc(data->input_tests_amount + 1, sizeof(char *));

	if (!data->input_tests_fd || !data->input_tests_name)
		exit_error(12, "Fail at allocate initial memory\n", data);
}
