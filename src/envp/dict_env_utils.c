/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_env_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 19:02:23 by gde-mora          #+#    #+#             */
/*   Updated: 2023/02/20 00:01:47 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

t_env	*create_dict_env(char *key, char *value);
void	dict_add_back(t_env **dict_env, char *key, char *value); //
void	dictclear(t_env *envp);

t_env	*create_dict_env(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = NULL;
	return (new_node);
}

t_env	*dictlast(t_env *dict_env)
{
	t_env	*last_env;

	last_env = dict_env;
	if (!dict_env)
		return (dict_env);
	while (last_env->next)
	{
		last_env = last_env->next;
	}
	return (last_env);
}

void	dict_add_back(t_env **dict_env, char *key, char *value) //front vai ficar ao contrário --mas gasta menos tempo pq n percorre... a n ser q pegue o tamanho 1 vez só e ja salve... --n da, pq vai ser sempre o tam anterior + 1... --mas da de fazer assim com tam + 1, consome medio, e fica igual
{
	t_env	*last_node;
	t_env	*new_node;

	if (!*dict_env)
		*dict_env = create_dict_env(key, value);
	else
	{
		last_node = dictlast(*dict_env);
		new_node = create_dict_env(key, value);
		last_node->next = new_node;
	}
}

void	dictclear(t_env *envp)
{
	if (envp)
	{
		dictclear(envp->next);
		free(envp->key);
		free(envp->value);
		free(envp);
	}
}
