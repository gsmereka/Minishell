/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/14 18:02:15 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_lexer(t_data *data)
{
	(void)data;
	//cria os tokens
	//expansor em mais tokens ($) ---isso vem antes do lexer   ---identifica se tem env na entrada, transforma em tokens no expansor e dps vem pra cá? ou expansor é chamado dentro do lexer? acho q expansor chama o lexer dps de pegar oq é a var de ambiente -> e transforma em token
	//vars de ambiente?
}