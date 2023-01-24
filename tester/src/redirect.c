/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:27:29 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/23 22:41:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static void	close_fds_at_error(int cmd, t_data *data);
static void redirect_error(int test, t_data *data);

void	redirect_input(int test, t_data *data)
{
	int	dup_work;

	dup_work = dup2(data->input_tests_fd[test], 0);
	if (dup_work == -1)
		redirect_error(test, data);
}

void	redirect_output(int test, t_data *data)
{
	int	dup_work;

	dup_work = dup2(data->user_outputs_fd[test], 1);
	if (dup_work == -1)
		redirect_error(test, data);
}

static void	redirect_error(int test, t_data *data)
{
	close(data->input_tests_fd[test]);
	close(data->user_outputs_fd[test]);
	exit_error(24, "Failed to execute dup2(2)", data);
}
