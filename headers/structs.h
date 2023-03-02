/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:23:49 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/01 20:27:36 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token //inicializar com bzero no lexer
{
	char			*type;
	char			*content; //o "token" na real seria só isso. O resto quem faz é o parser, n?
	char			**args;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	t_token	*tokens;
	t_env	*dict_envp;
	char	**virtual_envp;
	char	*prompt;
	char	*user_input;
	char	*error_msg;
	char	*last_pwd;
	int		exit_status;
}	t_data;

#endif