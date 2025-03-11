/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:44:18 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/09 15:45:54 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	int	count;

	count = 0;
	count += write(1, &c, 1);
	return (count);
}
/*int	main(void)
{
	char c = '%';
	ft_putchar(c);
	return (0);
}*/