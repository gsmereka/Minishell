/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 22:30:30 by gde-mora          #+#    #+#             */
/*   Updated: 2023/04/01 04:12:56 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	expand_env(char ***content, int i, t_data *data, char **new_content)
{
	char	*envp;
	char	*aux;
	t_env	*dict_envp;
	int		found_env;
	char	*new_word;

	i++;
	envp = NULL;
	dict_envp = data->dict_envp;
	found_env = 0;
//	new_word = NULL;
	new_word = ft_calloc(i + 1, sizeof(char)); // + 1 ou n?
	ft_strlcpy(new_word, **content, i); //e se o i for negativo? se $ tiver no 0, aí ali vira 1, e aq volta 0(?)
	while ((**content)[i] && (**content)[i] != ' ' && (**content)[i] != '"' && (**content)[i] != '\''  && (**content)[i] != '$')
	{
		aux = malloc(2);
		aux[0] = (**content)[i];
		aux[1] = '\0';
		envp = ft_strjoin_gnl(envp, aux);
		free(aux);
		i++;
	}
	while (dict_envp)
	{
		if (ft_strcmp(dict_envp->key, envp) == 0)
		{
			new_word = ft_strjoin_gnl(new_word, dict_envp->value);
		//	new_word = ft_strjoin_gnl(new_word, ft_substr(**content, i, ft_strlen(**content) - i));
		/*	free(**content);
			**content = ft_strdup(new_word);
			free(new_word);*/
			//tenho q substituir até o i pelo env->value
			*new_content = ft_strdup(new_word);
			found_env = 1;
			break ;
		}
		dict_envp = dict_envp->next;
	}
	if (found_env == 0)
	{
		new_word = ft_strjoin_gnl(new_word, ft_substr(**content, i, ft_strlen(**content) - i));
		*new_content = ft_strdup(new_word);
	/*	free(**content);
		**content = ft_strdup(new_word);
		free(new_word); //ta dando problema de espaço a mais quando vai juntar o token, colocar verificação de token vazio, n dar espaço (remover ele?)
	*/
	}
		//apagar até o i
	i--;
	return i;
}

void	expand_content(t_data *data, char **content)
{
	int		i;
//	int		j;
	char	*new_content;

	if (!content || !*content)
		return ;
	i = 0;
//	j = 0;
	new_content = NULL;
	while ((*content)[i]) //eu to percorrendo o content enquanto altero o content, isso n vai dar certo --mas se eu n alterar, n posso dar join com o content la dentro
	{
		if ((*content)[i] == '$')
			expand_env(&content, i, data, &new_content); // += ou =?     //recebe j pra continuar o new content? ou só join nele?
		else if ((*content)[i] == '"')
			ft_printf("aspas\n"); //aqui vai ter i += tamanho da palavra dentro das aspas --dentro desse chama o outro q ja existe pra substituir esse pedaço?
		i++;
	}
	if (new_content)
	{
		free(*content);
		*content = ft_strdup(new_content);
		free(new_content);
	}
}
