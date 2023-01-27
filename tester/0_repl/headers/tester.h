/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:35:53 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/26 12:08:09 by gsmereka         ###   ########.fr       */
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
# include <sys/stat.h>

// initialize
void		initialize(char *envp[], t_data *data);

// valgrind_path
void		set_valgrind_path(t_data *data);

// finalize
void		finalize(t_data *data);
void		exit_error(int error, char *msg, t_data *data);

// test_loop
void		test_input_loop(t_data *data);

// redirections
void		redirect_input(int test, t_data *data);
void		redirect_output(int test, t_data *data);
void		redirect_error(int test, t_data *data);

// verify_results
void		verify_results(t_data *data);
int			check_leaks(int test, t_data *data);

// utils
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
char		*ft_substr(char const *s, unsigned int start, size_t len);

#endif
