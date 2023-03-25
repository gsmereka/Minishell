/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:55:25 by gsmereka          #+#    #+#             */
/*   Updated: 2023/03/25 19:31:12 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static long int	ft_calculate_str_size(long int n, long int is_negative);
static char		*set_str(long int is_negative, long int str_size, long int n);

char	*ft_litoa(long int n)
{
	char		*str;
	long int	is_negative;
	long int		str_size;

	if (n <= -9223372036854775807)
		return (ft_strdup("-9223372036854775807"));
	if (n == 0)
		return (ft_strdup("0"));
	if (n < 0)
		is_negative = 1;
	else
		is_negative = 0;
	str_size = ft_calculate_str_size(n, is_negative);
	str = set_str(is_negative, str_size, n);
	return (str);
}

static char	*set_str(long int is_negative, long int str_size, long int n)
{
	long int		limit;
	char		*str;

	limit = 0;
	str = (char *)ft_calloc((str_size + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (is_negative)
	{
		limit = 1;
		str[0] = '-';
		n = n * (-1);
	}
	while (str_size > limit)
	{
		str[str_size - 1] = (n % 10) + '0';
		n = n / 10;
		str_size--;
	}
	return (str);
}

static long int	ft_calculate_str_size(long int n, long int is_negative)
{
	long int	str_size;

	str_size = 0;
	while (n != 0)
	{
		n = n / 10;
		str_size++;
	}
	if (is_negative)
		str_size++;
	return (str_size);
}
