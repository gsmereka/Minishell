/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:35:53 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/23 21:30:46 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H
# include "./structs.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

// initialize
void	initialize(t_data *data);

// finalize
void	finalize(t_data *data);
void	exit_error(int error, char *msg, t_data *data);

// test_loop
void	test_input_loop(t_data *data);
void	execute_test(int test, t_data *data);

// redirections
void	redirect_input(int test, t_data *data);
void	redirect_output(int test, t_data *data);

#endif