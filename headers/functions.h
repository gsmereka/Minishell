/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:23:28 by gde-mora          #+#    #+#             */
/*   Updated: 2023/02/26 18:55:57 by gsmereka         ###   ########.fr       */
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

//built in
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>

// REPL
void	init_repl(t_data *data);
void	init_repl_signals_handling(t_data *data);

// envp
void	set_initial_envp(char **envp, t_data *data);
t_env	*create_dict_env(char *key, char *value); //n precisa desse aqui(?)
void	dict_add_back(t_env **dict_env, char *key, char *value);
void	dictclear(t_env *envp);
void	att_virtual_envp(t_data *data);
void	att_envp_exitstatus_var(t_data *data);

// expander
void	init_expander(t_data *data);

// lexer
void	init_lexer(t_data *data);

// parser
void	init_parser(t_data *data);

// executor
void	init_executor(t_data *data);

// built_in
void	ft_cd(char **args, t_data *data);
void	ft_echo(char **args, t_data *data);
void	ft_env(char **args, t_data *data);
void	ft_exit(char **args, t_data *data);
void	ft_export(char **args, t_data *data);
void	ft_pwd(char **args, t_data *data);
void	ft_unset(char **args, t_data *data);

// end_program
void	end_program(t_data *data);
void	exit_error(int error_value, char *msg, t_data *data);
void	free_array_list(void **list);

#endif