/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_dec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-19 11:12:44 by pablalva          #+#    #+#             */
/*   Updated: 2024-11-19 11:12:44 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_str_is_dec(char *nb)
{
	int	point_found;

	point_found = 0;
	if (*nb == '+' || *nb == '-')
		nb++;
	if (*nb == '\0')
		return (0);
	while (*nb)
	{
		if (*nb == '.')
		{
			if (point_found)
				return (0);
			point_found = 1;
		}
		else if (!(ft_isdigit(*nb)))
			return (0);
		nb++;
	}
	return (1);
}
