/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_leaks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:14:38 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/25 14:16:51 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tester.h"

static long int	get_content_size(char *file_name, t_data *data);
static int	read_content(char *content, int test, t_data *data);

int	check_leaks(int test, t_data *data)
{
	long int	size;
	char		*content;
	int			leaks;

	size = get_content_size(data->user_error_name[test], data);
	content = calloc(size + 1, sizeof(char));
	if (!content)
		exit_error(12, "Fail at allocate user error memory\n", data);
	read_content(content, test, data);
	if (strstr(content, "All heap blocks were freed -- no leaks are possible") && strstr(content, "ERROR SUMMARY: 0 errors from 0 contexts"))
		leaks = 0;
	else
		leaks = 1;
	free(content);
	return (leaks);
}

static long int	get_content_size(char *file_name, t_data *data)
{
	struct		stat st;
	long int	size;

	if (stat(file_name, &st) == 0)
		size = st.st_size;
	else
		exit_error(1, "Fail at get file size\n", data);
	if (!size)
		exit_error(1, "Empty File\n", data);
	return (size);
}

static int	read_content(char *content, int test, t_data *data)
{
	int		status_1;
	char	expected[1];

	expected[0] = 0;
	status_1 = 1;
	while (status_1)
	{
		status_1 = read(data->user_error_fd[test], &expected, 1);
		if (status_1 < 0)
			return (0);
		if (expected[0] != '\0')
			*content = expected[0];
		content++;
	}
	return (1);
}
