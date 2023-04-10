/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:14:07 by gsmereka          #+#    #+#             */
/*   Updated: 2023/04/10 22:31:47 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_token
{
	char			*type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				hidden_status;			
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char	*name;
	char	**args;
	int		**heredocs_pipes;
	int		*files_fd;
	char	**files;
	int		*files_modes;
}	t_cmd;

typedef struct s_exec
{
	t_cmd	**cmds;
	int		cmds_amount;
	int		*pid;
	int		*status;
	int		**pipes;
	char	**env_paths;
}	t_exec;

typedef struct s_expand_aux
{
	int		simple_quote;
	int		double_quote;
	char	*new_content;
	char	*aux;
}	t_expand_aux;

typedef struct s_data
{
	t_token	*tokens;
	t_env	*dict_envp;
	t_exec	*exec;
	char	**virtual_envp;
	char	*prompt;
	char	*user_input;
	char	*error_msg;
	int		exit_status;
	int		lines;
	int		output_save_fd;
	int		input_save_fd;
	int		need_interrupt;
}	t_data;

#endif