/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/02/23 05:44:26 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	init_lexer(t_data *data) //oq faz: separar a string por palavras   --- atenção nas aspas!   
{
	//bzero na struct de token
	//retira espaços do começo e fim
	//procura aspas ('' e ""?), subtitui espaços dentro das aspas pelo numero 1 (em decimal) de ascii
	//split nos espaços
	//volta aqueles ascii 1 p espaço?
	//salva cada split desse num nó de token
	

	//ver expansor dps -- fazer lexer basico antes
	//expansor em mais tokens ($) ---isso vem antes do lexer   ---identifica se tem env na entrada, transforma em tokens no expansor e dps vem pra cá? ou expansor é chamado dentro do lexer? acho q expansor chama o lexer dps de pegar oq é a var de ambiente -> e transforma em token
	//vars de ambiente?
	
	//cria os tokens
	ft_printf("%s\n", data->user_input); // ele n ta tirando os espaços
}
