/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:54:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/24 21:54:47 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_redirect(t_token *token)
{
	if (is_reserved("<", token))
		return (1);
	else if (is_reserved("<<", token))
		return (1);
	else if (is_reserved(">", token))
		return (1);
	else if (is_reserved(">>", token))
		return (1);
	return (0);
}
