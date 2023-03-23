/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reserved.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:13:54 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/23 11:23:36 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/minishell.h"

int	is_reserved(char *word, t_token *token)
{
	// if (!token->type)
	// 	return (0);
	if (ft_strcmp(token->content, word) == 0)
		return (1);
	return (0);
}
