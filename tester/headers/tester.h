/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 22:35:53 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/22 23:23:24 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H
# include "./structs.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

// initialize
void	initialize(t_data *data);

// finalize
void	finalize(t_data *data);
void	exit_error(int error, char *msg, t_data *data);

#endif