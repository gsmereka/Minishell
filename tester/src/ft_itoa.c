/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsmereka <gsmereka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 21:55:25 by gsmereka          #+#    #+#             */
/*   Updated: 2023/01/24 20:24:29 by gsmereka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/tester.h"

static size_t	ft_calculate_str_size(int n, int is_negative);
static char		*set_str(int is_negative, size_t str_size, int n);

char	*ft_itoa(int n)
{
	char	*str;
	int		is_negative;
	size_t	str_size;

	if (n <= -2147483648)
		return (strdup("-2147483648"));
	if (n == 0)
		return (strdup("0"));
	if (n < 0)
		is_negative = 1;
	else
		is_negative = 0;
	str_size = ft_calculate_str_size(n, is_negative);
	str = set_str(is_negative, str_size, n);
	return (str);
}

static char	*set_str(int is_negative, size_t str_size, int n)
{
	size_t		limit;
	char		*str;

	limit = 0;
	str = (char *)calloc((str_size + 1), sizeof(char));
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

static size_t	ft_calculate_str_size(int n, int is_negative)
{
	size_t	str_size;

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
