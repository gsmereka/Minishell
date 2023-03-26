/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_error_msg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 20:27:57 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/26 20:06:45 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static void	print_cd_error(char *prefix, char *name, char *sufix);

void	ft_cd_error_msg(int error, char *name, t_data *data)
{
	char		*error_msg;

	if (error == 1)
	{
		error_msg = "bash: cd: too many arguments\n";
		write(2, error_msg, ft_strlen(error_msg));
	}
	else if (error == 2)
	{
		print_cd_error("bash: cd: ", name, ": Not a directory\n");
	}
	else if (error == 3)
	{
		print_cd_error("bash: cd: ", name, ": Permission denied\n");
	}
	else if (error == 4)
		write(2, "bash: cd: HOME not set\n",
			ft_strlen("bash: cd: HOME not set\n"));
	else if (error == 5)
		print_cd_error("bash: cd: ", name,
			": No such file or directory\n");
	att_exit_status(1, data);
}

static void	print_cd_error(char *prefix, char *name, char *sufix)
{
	char	*error_msg;

	error_msg = ft_strjoin(prefix, name);
	error_msg = ft_strjoin_with_free(error_msg, sufix);
	write(2, error_msg, ft_strlen(error_msg));
	if (error_msg)
		free(error_msg);
}
