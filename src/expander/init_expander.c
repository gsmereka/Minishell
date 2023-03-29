/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/29 22:30:44 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	creck_token_in_envp(t_data *data, char *content, t_token **env_token)
{
	t_env	*aux_env;

	//fazer split por $ no token!
	aux_env = data->dict_envp;
	while (aux_env)
	{
		if (ft_strcmp(aux_env->key, content) == 0) 
		{
			free((*env_token)->content);
			(*env_token)->content = ft_strdup(aux_env->value); //e se alterar a env?
			return (1);
		}
		aux_env = aux_env->next;
	}
	free((*env_token)->content);
//	(*env_token)->prev->next = (*env_token)->next; //implementar prev? ou driblar de outra forma? -taok ja, eu acho
	(*env_token)->content = ft_strdup("");  //tem problemas com espaço nas envp vazias --ta normal agr
	return (0);
}

void	init_expander(t_data *data)
{
	t_token	*aux_token;
	char	*new_content;
	char	*aux_trim;

	aux_token = data->tokens;
	while (aux_token)
	{
		new_content = NULL;
		aux_trim = NULL;
		if (aux_token->content[0] == '$') //arrumar $oi$oi e $oi"teste" e $oi'teste' etc --reutilizar funções
		//	check_envp_position_in_token(data, &aux_token->content); da errado
			creck_token_in_envp(data, &aux_token->content[1], &aux_token); //checar se encontra aspas! simples e dupla ( ) ( )
		else if (aux_token->content[0] == '"') //tenho q dar free nas matriz em caso de erro(?) --atenção leaks, checar muito!
		{
			new_content = ft_strtrim(aux_token->content, "\"");
			free(aux_token->content);
			aux_token->content = ft_strdup(new_content);
			free(new_content);
			check_envp_position_in_token(data, &aux_token->content);
			aux_trim = ft_strtrim(aux_token->content, " ");
			free(aux_token->content);
			aux_token->content = ft_strdup(aux_trim);
			free(aux_trim);
		}
		else if (aux_token->content[0] == '\'')
		{
			new_content = ft_strtrim(aux_token->content, "\'");
			free(aux_token->content);
			aux_token->content = ft_strdup(new_content);
			free(new_content);
			//ft_strtrim nas aspas simpes!
		}
		// ---atenção para "''" e '""'
		//ft_printf("%s\n", aux_token->content);
		aux_token = aux_token->next;
	}
}

//parser só vai testar os redirects -- syntax errors...

//echo teste >| ls      --cria o arquivo ls  ---mas isso é um tipo de redirect, n vms aceitar (vms tratar como 2)
//echo teste > | ls     --bash: syntax error near unexpected token `|'   --são dois redirects
