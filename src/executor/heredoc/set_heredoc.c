/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:05:02 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 21:36:57 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	set_heredoc(t_data *data)
{
	heredoc_signals_handling(data);
	if (!heredoc_cmd_loop(data))
		return (0);
	return (1);
}
