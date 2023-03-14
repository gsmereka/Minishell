/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_leaks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:14:38 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/14 18:53:02 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/tester.h"

static long int	get_content_size(char *file_name, t_data *g_data);
static int		read_content(char *content, int test, t_data *g_data);
static char		*get_valgrind_test_content(int test, t_data *g_data);
static int		readline_leaks(char *content);

int	check_leaks(int test, t_data *g_data)
{
	char	*content;
	int		leaks;

	leaks = 0;
	content = get_valgrind_test_content(test, g_data);
	if (content)
	{
		if (!strstr(content,
				"All heap blocks were freed -- no leaks are possible"))
			leaks = 1;
		if (leaks && !readline_leaks(content) != 0)
			leaks = 0;
		if (!strstr(content, "ERROR SUMMARY: 0 errors from 0 contexts"))
			leaks = 1;
		free(content);
	}
	return (leaks);
}

static long int	get_content_size(char *file_name, t_data *g_data)
{
	struct stat	st;
	long int	size;

	if (stat(file_name, &st) == 0)
		size = st.st_size;
	else
		exit_error(1, "Fail at get file size\n", g_data);
	if (!size)
		exit_error(1, "Empty File\n", g_data);
	return (size);
}

static char	*get_valgrind_test_content(int test, t_data *g_data)
{
	long int	size;
	char		*content;

	size = get_content_size(g_data->user_error_name[test], g_data);
	content = calloc(size + 2, sizeof(char));
	if (!content)
		exit_error(12, "Fail at allocate user error memory\n", g_data);
	read_content(content, test, g_data);
	return (content);
}

static int	read_content(char *content, int test, t_data *g_data)
{
	int		status_1;
	char	expected[1];

	expected[0] = 0;
	status_1 = 1;
	while (status_1)
	{
		status_1 = read(g_data->user_error_fd[test], &expected, 1);
		if (status_1 < 0)
			return (0);
		if (expected[0] != '\0')
			*content = expected[0];
		content++;
	}
	return (1);
}

static int	readline_leaks(char *content)
{
	int	leaks;

	leaks = 0;
	if (!strstr(content, "definitely lost: 0 bytes in 0 blocks"))
		leaks = 1;
	if (!strstr(content, "indirectly lost: 0 bytes in 0 blocks"))
		leaks = 1;
	if (!strstr(content, "possibly lost: 0 bytes in 0 blocks"))
		leaks = 1;
	if (!strstr(content, "still reachable: 0 bytes in 0 blocks"))
		leaks = 1;
	return (leaks);
}
