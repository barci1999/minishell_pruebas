/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_valid_num.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-01-17 12:10:10 by pablalva          #+#    #+#             */
/*   Updated: 2025-01-17 12:10:10 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_is_valid_num(char *nbr)
{
	int	i;

	i = 1;
	if (ft_is_sing(nbr[0]) || ft_isdigit(nbr[0]))
	{
		if (ft_is_sing(nbr[0]) && nbr[i] == '\0')
			return (0);
		while (ft_isdigit(nbr[i]) || nbr[i] == '\0')
		{
			if (nbr[i] == '\0')
				return (1);
			i++;
		}
	}
	return (0);
}
