/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_interrupt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:36:18 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 22:52:27 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	heredoc_interrupt(char *input, char *limiter, t_data *data)
{
	char	*msg;

	if (input != NULL)
		return (0);
	if (data->exec->need_interrupt)
		return (0);
	msg = ft_strdup("\nbash: warning: here-document "\
		"delimited by end-of-file (wanted `");
	msg = ft_strjoin_with_free(msg, limiter);
	msg = ft_strjoin_with_free(msg, "')\n");
	if (msg != NULL)
	{
		write(2, msg, ft_strlen(msg));
		free(msg);
	}
	return (1);
}
