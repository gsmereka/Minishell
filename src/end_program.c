/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 17:36:43 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

static void	free_data(t_data *g_data);

// Saida normal do minishell, atraves do ctrl + D ou do comando exit.
void	end_program(t_data *g_data) //comentarios em portugues
{
	int	exit_status;

	exit_status = g_data->exit_status;
	free_data(g_data);
	exit(exit_status);
}

// Saída pra quando houver algum erro interno,
// como falha na alocação de memorioa e etc...
void	exit_error(int error_value, char *msg, t_data *g_data)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_data(g_data);
	exit(error_value);
}

static void	free_data(t_data *g_data)
{
	if (g_data->dict_envp)
		dictclear(g_data->dict_envp);
	if (g_data->user_input)
		free(g_data->user_input);
	if (g_data->virtual_envp)
		free_array_list((void **)g_data->virtual_envp);
	if (g_data->tokens)
		token_clear(&g_data->tokens);
	if (g_data->exec)
		clear_commands(g_data);
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
