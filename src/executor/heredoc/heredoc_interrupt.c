/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_interrupt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 21:36:18 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/20 18:25:49 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	heredoc_interrupt(char *input, char *limiter, t_data *data)
{
	char	*msg;
	char	*line;

	if (input != NULL)
		return (0);
	if (data->exec->need_interrupt)
		return (0);
	line = ft_strdup("113");
	msg = ft_strjoin("\nbash: warning: here-document "\
		"at line ", line);
	free(line);
	msg = ft_strjoin_with_free(msg, " delimited by end-of-file (wanted `");
	msg = ft_strjoin_with_free(msg, limiter);
	msg = ft_strjoin_with_free(msg, "')\n");
	if (msg != NULL)
	{
		write(2, msg, ft_strlen(msg));
		free(msg);
	}
	return (1);
}
