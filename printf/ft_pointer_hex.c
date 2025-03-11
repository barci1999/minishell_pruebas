/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:31:27 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/09 17:32:25 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pointer_hex(unsigned long long nb, char *base, int flag)
{
	unsigned long long	size;
	unsigned long long	num;
	int					count;

	count = 0;
	if (!nb)
	{
		count += ft_putstr("(nil)");
		return (count);
	}
	num = nb;
	size = ft_strlen(base);
	if (flag)
		count += ft_putstr("0x");
	if (num >= size)
		count += ft_pointer_hex(nb / size, base, 0);
	count += write(1, &base[num % size], 1);
	return (count);
}
