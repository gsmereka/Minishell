/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 21:27:29 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static void	close_fds_at_error(int cmd, t_data *g_data);
static void	close_fds_at_error(int test, t_data *g_data);

void	redirect_input(int test, t_data *g_data)
{
	int	dup_work;

	dup_work = dup2(g_data->input_tests_fd[test], 0);
	if (dup_work == -1)
		close_fds_at_error(test, g_data);
}

void	redirect_output(int test, t_data *g_data)
{
	int	dup_work;

	dup_work = dup2(g_data->user_outputs_fd[test], 1);
	if (dup_work == -1)
		close_fds_at_error(test, g_data);
}

void	redirect_error(int test, t_data *g_data)
{
	int	dup_work;

	dup_work = dup2(g_data->user_error_fd[test], 2);
	if (dup_work == -1)
		close_fds_at_error(test, g_data);
}

static void	close_fds_at_error(int test, t_data *g_data)
{
	close(g_data->input_tests_fd[test]);
	close(g_data->user_outputs_fd[test]);
	close(g_data->user_error_fd[test]);
	exit_error(24, "Failed to execute dup2(2)", g_data);
}
