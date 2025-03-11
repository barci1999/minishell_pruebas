/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:52:14 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/09 15:45:30 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_putstr(const char *s)
{
	int	count;

	count = 0;
	if (!s)
	{
		count += ft_putstr("(null)");
		return (count);
	}
	count = write(1, s, ft_strlen(s));
	return (count);
}
/*int main(void)
{
	int result = 0;
	const char *s = "cocacola";
	ft_putstr(s);
	return(0);
}*/