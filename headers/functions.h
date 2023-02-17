/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:23:28 by gde-mora          #+#    #+#             */
/*   Updated: 2023/02/17 22:33:32 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H
# include "structs.h"

// REPL
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

void	init_repl(t_data *data);
void	init_repl_signals_handling(t_data *data);

// expander
void	init_expander(t_data *data);
t_env	*create_dict_env(char *key, char *value);
void	dict_add_back(t_env **dict_env, char *key, char *value);
void	dictclear(t_env *envp);

// lexer
void	init_lexer(t_data *data);

// parser
void	init_parser(t_data *data);

// executor
void	init_executor(t_data *data);

#endif