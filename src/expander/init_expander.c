/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_expander.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:48:55 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/08 01:09:11 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	creck_token_in_envp(t_data *data, char *content, t_token **env_token)
{
	t_env	*aux_env;

	aux_env = data->dict_envp; //colocar um if p o caso da aspas, talvez com uma flag? flag quotes
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
	(*env_token)->content = ft_strdup(" ");
	return (0);
}

/*t_token	*check_envp_position_in_token(char **content)
{
	char	**token;

	token = ft_split(*content, ' '); //divide o token por espaços --e se n tiver espaços?
	i = 0;
	while (token[i])
	{
		envp_token = ft_split(token[i], '$');
		while (envp_token[j])
		{
			if (envp_token[j][0] == '$')
		}
		i++;
	}
}*/

void	init_expander(t_data *data)
{
	t_token	*aux_token;

	aux_token = data->tokens;
	while (aux_token)
	{
		if (aux_token->content[0] == '$') //cuidado com as aspas! --checkar '', "" e contra barra?--acho q \ n
			creck_token_in_envp(data, &aux_token->content[1], &aux_token); //coloco o +1 aq ja p avançar o $? --sim
	//	else if (aux_token->content[0] == '"') //mas e  '"$algo"'? -- shell: printa "$algo"
	//		check_envp_position_in_token(&aux_token->content);
			
		// char *envp_in_token = -- procurar o $ (dentro dos caracteres do token), ir até o espaço ou \0 e pegar a palavra
		// creck_token_in_envp(data, &envp_in_token, &aux_token);  --na vdd, ele n pode substituir td, ele tem q substituir só naquele lugar, concatenando com os outros
		// mas com as '' no começo tbm tem caso q exibe oq tem em $... -- só preciso tratar a primeira aspas (ou a segunda tbm?)
		aux_token = aux_token->next;
	}
}

// msg de erro p aspas n fechadas
// no token colocar se é token especial (tipo <, >, | etc)
// dps tem q buscar os q são comandos e adc no token tbm, pq o parser vai testar se faz sentido. exemplo: cmd cmd n faz sentido (?)  cat cat cat -- 2 no such file ou directory  -- cat cat cat ls tbm (3 agr) --- cat cat cat Makefile  -funciona o último... o cat pega oq vem em seguida como argumento --se n tem outro arg, abre pra escrever e mostra oq mandar, ate dar ctrl C

//echo teste >| ls      --cria o arquivo ls
//echo teste > | ls     --bash: syntax error near unexpected token `|'
//aparentemente eles usam strncmp :P