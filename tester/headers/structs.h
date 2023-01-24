/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:34:12 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/24 20:07:18 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_process
{
	int		*status;
	int		*pid;
}	t_process;

typedef struct s_data
{
	t_process	process;
	char	**envp;
	int		original_stdin;
	int		original_stdout;
	int		input_tests_amount;
	int		*input_tests_fd;
	int		*expected_outputs_fd;
	int		*user_outputs_fd;
	char 	**input_tests_name;
	char 	**expected_outputs_name;
	char 	**user_outputs_name;
}	t_data;

#endif
