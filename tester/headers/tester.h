/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:35:53 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/24 20:24:59 by gsmereka         ###   ########.fr       */
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
# include <fcntl.h>

// initialize
void	initialize(char *envp[], t_data *data);
char	*ft_itoa(int n);

// finalize
void	finalize(t_data *data);
void	exit_error(int error, char *msg, t_data *data);

// test_loop
void	test_input_loop(t_data *data);

// redirections
void	redirect_input(int test, t_data *data);
void	redirect_output(int test, t_data *data);

// verify_results
void	verify_results(t_data *data);

#endif