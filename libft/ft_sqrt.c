/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-21 12:14:22 by pablalva          #+#    #+#             */
/*   Updated: 2025-01-21 12:14:22 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_sqrt(int num)
{
	int	i;

	if (num < 4)
		return (1);
	i = 2;
	while (i * i < num)
	{
		i++;
	}
	if (i * i > num)
	{
		if ((i * i - num) < ((i - 1) * (i - 1) + (-num)))
			return (i);
	}
	return (i - 1);
}
