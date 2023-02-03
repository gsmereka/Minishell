/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:23:49 by gde-mora          #+#    #+#             */
/*   Updated: 2023/02/03 13:39:30 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	char			*type;
	char			*content;
	char			**args;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_token	*tokens;
	t_env	*linked_envp;
	char	**envp;
	char	*prompt;
	char	*user_input;
}	t_data;

#endif