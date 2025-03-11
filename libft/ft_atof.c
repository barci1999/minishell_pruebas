/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-18 14:12:11 by pablalva          #+#    #+#             */
/*   Updated: 2024-11-18 14:12:11 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static double	take_sign(char *nb, int *i)
{
	double	sign;

	sign = 1.0;
	if (nb[*i] == '-' || nb[*i] == '+')
	{
		if (nb[*i] == '-')
			sign = -1.0;
		(*i)++;
	}
	return (sign);
}

static double	handle_decimal_part(char *nb, int *i)
{
	double	decimal_part;
	double	result;

	decimal_part = 1.0;
	result = 0.0;
	while (nb[*i] && ft_isdigit(nb[*i]))
	{
		decimal_part *= 10;
		result += (nb[*i] - '0') / decimal_part;
		(*i)++;
	}
	return (result);
}

double	ft_atof(char *nb)
{
	int		i;
	double	result;
	double	sign;

	i = 0;
	result = 0.0;
	sign = 1.0;
	sign = take_sign(nb, &i);
	while (nb[i] && ft_isdigit(nb[i]))
	{
		result = result * 10 + (nb[i] - '0');
		i++;
	}
	if (nb[i] == '.')
	{
		i++;
		result += handle_decimal_part(nb, &i);
	}
	return (result * sign);
}
