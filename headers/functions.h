/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:23:28 by gde-mora          #+#    #+#             */
/*   Updated: 2023/02/23 04:05:57 by gde-mora         ###   ########.fr       */
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

// envp
void	set_initial_envp(char **envp, t_data *data);
t_env	*create_dict_env(char *key, char *value); //n precisa desse aqui(?)
void	dict_add_back(t_env **dict_env, char *key, char *value);
void	dictclear(t_env *envp);

// expander
void	init_expander(t_data *data);

// lexer
void	init_lexer(t_data *data);

// parser
void	init_parser(t_data *data);

// executor
void	init_executor(t_data *data);

// built_in
void	ft_cd(t_data *data);
void	ft_echo(t_data *data);
void	ft_env(t_data *data);
void	ft_exit(t_data *data);
void	ft_export(t_data *data);
void	ft_pwd(t_data *data);
void	ft_unset(t_data *data);

// end_program
void	end_program(t_data *data);
void	exit_error(int error_value, char *msg, t_data *data);

#endif