/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/05 00:26:50 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && (s1[i]) && (s2[i]))
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}

int	creck_token_in_envp(t_data *data, char *content, t_token **env_token)
{
	t_env	*aux_env;

	aux_env = data->dict_envp;
	while (aux_env)
	{
		if (ft_strcmp(aux_env->key, content) == 0) //qual ft_strlen é apropriado?? de content ou do key? --nenhum! 
		{
			free((*env_token)->content);
			(*env_token)->content = ft_strdup(aux_env->value); //e se alterar a env?
			return (1);
		}
		aux_env = aux_env->next;
	}
	free((*env_token)->content);
	(*env_token)->content = ft_strdup(" ");
	return (0);
}

void	init_expander(t_data *data)
{
	t_token	*aux_token;

	aux_token = data->tokens;
	while (aux_token)
	{
		if (aux_token->content[0] == '$')
			creck_token_in_envp(data, &aux_token->content[1], &aux_token); //coloco o +1 aq ja p avançar o $? --sim
		aux_token = aux_token->next;
	}
}
