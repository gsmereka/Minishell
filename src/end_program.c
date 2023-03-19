/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:36:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/19 20:52:29 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	free_data(t_data *data);
static int	close_all_fds(t_data *data);
static void	close_files(int *files);

// Saida normal do minishell, atraves do ctrl + D ou do comando exit.
void	end_program(t_data *data) //comentarios em portugues
{
	int	exit_status;

	exit_status = data->exit_status;
	free_data(data);
	exit(exit_status);
}

// Saída pra quando houver algum erro interno,
// como falha na alocação de memorioa e etc...
void	exit_error(int error_value, char *msg, t_data *data)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_data(data);
	exit(error_value);
}

static void	free_data(t_data *data)
{
	if (data->dict_envp)
		dictclear(data->dict_envp);
	if (data->user_input)
		free(data->user_input);
	if (data->virtual_envp)
		free_array_list((void **)data->virtual_envp);
	if (data->tokens)
		token_clear(&data->tokens);
	if (data->exec)
		clear_commands(data);
	rl_clear_history();
}

void	free_array_list(void **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

static int	close_all_fds(t_data *data)
{
	int	i;

	i = 0;
	if (!data->exec)
		return (0);
	while (i < data->exec->cmds_amount)
	{
		if (data->exec->pipes)
		{
			if (data->exec->pipes[i][1] != -1)
				close(data->exec->pipes[i][1]);
			if (data->exec->pipes[i][0] != -1)
				close(data->exec->pipes[i][0]);
		}
		if (data->exec->cmds)
		{
			close_files(data->exec->cmds[i]->infiles_fd);
			close_files(data->exec->cmds[i]->outfiles_fd);
		}
		i++;
	}
	return (0);
}

static void	close_files(int *files)
{
	int	i;

	i = 0;
	if (files)
	{
		while (files[i])
		{
			if (files[i] != -1)
				close (files[i]);
			i++;
		}
	}
}
