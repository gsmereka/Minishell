/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reserved.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 11:13:54 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/09 11:20:49 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_reserved(char *word, char *reserved_word)
{
	// if (!token->type)
	// 	return (0);
	if (ft_strncmp(word, reserved_word, ft_strlen(word)) == 0)
		return (1);
	return (0);
}
