/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:30:54 by gde-mora          #+#    #+#             */
/*   Updated: 2023/02/21 18:31:06 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// :)
#include "../headers/minishell.h"

static void	print_envp(t_data *data);

void	set_initial_envp(char **envp, t_data *data)
{
	int	i;
	int	j;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] != '=')
			j++;
		key = malloc(j + 2); // +2 ou +1?       --tamanho
		ft_strlcpy(key, envp[i], j + 1); // --tamanho
		value = ft_strdup(&envp[i][j + 1]); //  -- posição    -- j == '='
		dict_add_back(&data->dict_envp, key, value); //front ou back?
		free(key);
		free(value); //sera q é por causa dos free?
		i++;
	}

	print_envp(data);
	//ft_printf("%s\n", data->dict_envp->key);
}

void	free_data(t_data *data)
{
	if (data->dict_envp)
		dictclear(data->dict_envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	data;

	(void)argc;
	(void)argv;
	(void)envp;
	ft_bzero(&data, sizeof(t_data));
//	ft_printf("%s\n", envp[0]); //tem envp 0 --e 00 tbm
	set_initial_envp(envp, &data);
//	init_repl(&data);
	char	**args;

	args = ft_calloc(3, sizeof(char *));
	args[0] = "";
	args[1] = "..";
	ft_cd(args, &data);
	free(args);
	print_envp(&data);
	free_data(&data); //a cada exit tem q liberar tbm
}

static void	print_envp(t_data *data)
{
	int	i;

	t_env *aux_print = data->dict_envp;
	i = 0;
	while (aux_print)
	{
		if (ft_strncmp(aux_print->key, "PWD", 4) == 0)
			ft_printf("key: %s\nvalor:%s\n", aux_print->key, aux_print->value);
		aux_print = aux_print->next;
		i++;
	}
}
