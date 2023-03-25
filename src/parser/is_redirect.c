/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 20:54:04 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/24 21:00:33 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	is_redirect(t_token *token, t_data *data)
{
	(void)data;
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
