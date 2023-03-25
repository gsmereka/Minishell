/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:23:28 by gde-mora          #+#    #+#             */
/*   Updated: 2023/03/24 20:56:50 by gsmereka         ###   ########.fr       */
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
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>

// Executor
# include <sys/wait.h>

// general
char	*ft_strjoin_with_free(char *s1, char *s2);

// SIGNALS
void	heredoc_signals_handling(t_data *data);
void	child_signals_handling(t_data *data);
void	init_repl_signals_handling(t_data *data);

// REPL
void	init_repl(t_data *data);
void	set_prompt(t_data *data);

// envp
void	set_initial_envp(char **envp, t_data *data);
void	dict_add_back(t_env **dict_env, char *key, char *value);
void	dictclear(t_env *envp);
void	att_virtual_envp(t_data *data);
void	att_exit_status(int exit_status, t_data *data);
t_env	*find_env(char *key, t_data *data);

// expander
void	init_expander(t_data *data);
int		ft_strcmp(char *s1, char *s2);

// lexer
void	init_lexer(t_data *data);
void	add_token(t_token **tokens, char *content);
void	token_clear(t_token **tokens);

// parser
void	init_parser(t_data *data);
int		check_syntax(t_data *data);
int		is_redirect(t_token *token, t_data *data);

// executor
void	init_executor(t_data *data);
void	clear_execution_data(t_data *data);
void	execute_built_in(t_cmd *cmd, t_data *data);
int		is_reserved(char *word, t_token *token);
int		get_commands_info(t_data *data);
void	format_cmd(t_token *token, t_cmd *cmd);
void	get_outputs(t_token *token, t_cmd *cmd);
void	get_inputs(t_token *token, t_cmd *cmd);
int		get_env_paths(t_data *data);
int		set_cmds_paths(t_data *data);
int		set_processes(t_data *data);
void	set_files(t_cmd *cmd, t_data *data);
int		redirect_input(int cmd, t_data *data);
int		redirect_output(int cmd, t_data *data);
void	execute(t_cmd *cmd, t_data *data);
char	*get_next_line_with_free(int fd, int stop);

// close_fds
int		close_all_fds(t_data *data);
void	close_parent_pipes_fds(int cmd, t_data *data);
void	close_files_fds(char **paths, int *files);;
void	close_cmd_pipes(int cmd_index, t_data *data);

// heredoc
int		set_heredoc(t_data *data);
int		heredoc_cmd_loop(t_data *data);
int		heredoc_eof_delimitation(char *input, char *limiter, t_data *data);
void	close_heredoc_pipes(t_data *data);
void	close_cmd_heredoc_pipes(t_cmd *cmd);

// built_in
void	ft_cd(char **args, t_data *data);
void	ft_echo(char **args, t_data *data);
void	ft_env(char **args, t_data *data);
void	ft_exit(char **args, t_data *data);
void	ft_export(char **args, t_data *data);
void	ft_pwd(char **args, t_data *data);
void	ft_unset(char **args, t_data *data);
void	ft_cd_error_msg(int error, char *name, t_data *data);
void	ft_export_error_msg(int error, char *name, t_data *data);
int		is_built_in(t_cmd *cmd);

// end_program
void	end_program(t_data *data);
void	exit_error(int error_value, char *msg, t_data *data);
void	free_array_list(void **list);

#endif