/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_initial_envp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:51:10 by gde-mora          #+#    #+#             */
/*   Updated: 2023/02/23 04:31:27 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	set_initial_envp(char **envp, t_data *data)
{
	int	i;
	int	j;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		key = malloc(j + 2); // +2 ou +1?       --tamanho
		ft_strlcpy(key, envp[i], j + 1); // --tamanho
		value = ft_strdup(&envp[i][j + 1]); //  -- posição    -- j == '='
		dict_add_back(&data->dict_envp, key, value); //front ou back?
		//ft_printf("%s : ", key);
		//ft_printf("%s\n", value);
		free(key);
		free(value); //sera q é por causa dos free?
		i++;
	}

	/*t_env *aux_print = data->dict_envp;
	i = 0;
	while (i < 5)
	{
		ft_printf("%s\n", aux_print->value);
		aux_print = aux_print->next;
		i++;
	}*/
	//ft_printf("%s\n", data->dict_envp->key);
}
