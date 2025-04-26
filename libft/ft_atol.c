/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 11:13:40 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/26 13:21:17 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static long	handle_overflow(long res, int sign, char next_digit)
{
	if (res > LONG_MAX / 10 || (res == LONG_MAX / 10 && next_digit > '7'))
	{
		if (sign == 1)
			return (LONG_MAX);
		else
			return (LONG_MIN);
	}
	return (0);
}

long	ft_atol(char *str)
{
	int		i;
	long	res;
	long	overflow_check;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	while (is_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		overflow_check = handle_overflow(res, sign, str[i]);
		if (overflow_check)
			return (overflow_check);
		res = res * 10 + (str[i++] - '0');
	}
	return (res * sign);
}
