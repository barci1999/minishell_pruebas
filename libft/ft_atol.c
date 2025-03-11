/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-15 11:13:40 by pablalva          #+#    #+#             */
/*   Updated: 2025-01-15 11:13:40 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static long	handle_overflow(long result, int sign, char next_digit)
{
	if (result > LONG_MAX / 10 || (result == LONG_MAX / 10 && next_digit > '7'))
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
	long	result;
	long	overflow_check;
	int		sign;

	i = 0;
	sign = 1;
	result = 0;
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
		overflow_check = handle_overflow(result, sign, str[i]);
		if (overflow_check)
			return (overflow_check);
		result = result * 10 + (str[i++] - '0');
	}
	return (result * sign);
}
