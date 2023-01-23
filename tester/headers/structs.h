/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:34:12 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/23 20:40:43 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_data
{
	int		input_tests_amount;
	int		*input_tests_fd;
	char 	**input_tests_name;
	char 	**expected_outputs_name;
	char 	**user_outputs_name;
}	t_data;

#endif
