/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 20:14:07 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/05 20:17:27 by gsmereka         ###   ########.fr       */
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
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef	struct s_cmd
{
	char			*name;
	char			**args;
	int				input_fd;
	int				output_fd;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_data
{
	t_token	*tokens;
	t_env	*dict_envp;
	t_cmd	*cmds;
	char	**virtual_envp;
	char	*prompt;
	char	*user_input;
	char	*error_msg;
	int		exit_status;
}	t_data;

#endif