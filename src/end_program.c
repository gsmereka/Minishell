/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:36:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/30 20:10:18 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	free_data(t_data *data);

void	end_program(t_data *data)
{
	int	exit_status;

	if (data->error_msg)
		ft_putstr_fd(data->error_msg, 2);
	exit_status = data->exit_status;
	close_all_fds(data);
	free_data(data);
	exit(exit_status);
}

void	exit_error(int error_value, char *msg, t_data *data)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	close_all_fds(data);
	free_data(data);
	exit(error_value);
}

static void	free_data(t_data *data)
{
	if (data->error_msg)
		free(data->error_msg);
	if (data->prompt)
		free(data->prompt);
	if (data->dict_envp)
		dictclear(data->dict_envp);
	if (data->user_input)
		free(data->user_input);
	if (data->virtual_envp)
		free_array_list((void **)data->virtual_envp);
	if (data->tokens)
		token_clear(&data->tokens);
	if (data->exec)
		clear_execution_data(data);
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
