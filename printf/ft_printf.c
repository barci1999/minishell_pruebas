/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 11:22:33 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/24 14:39:06 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

static int	assig_ft(char const *format, int *res, int *p, va_list args)
{
	if (format[*p] == 's')
		*res += ft_putstr(va_arg(args, char *));
	else if (format[*p] == 'c')
		*res += ft_putchar(va_arg(args, int));
	else if (format[*p] == 'd' || format[*p] == 'i')
		*res += ft_putnbr(va_arg(args, int));
	else if (format[*p] == 'u')
		*res += ft_putnbrnu(va_arg(args, unsigned int));
	else if (format[*p] == 'p')
		*res += ft_pointer_hex(va_arg(args, unsigned long),
				"0123456789abcdef", 1);
	else if (format[*p] == 'x')
		*res += ft_hexadec(va_arg(args, unsigned int), "0123456789abcdef");
	else if (format[*p] == 'X')
		*res += ft_hexadec(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (format[*p] == '%')
		*res += ft_putchar('%');
	return (*res);
}

int	ft_printf(char const *format, ...)
{
	va_list	args;
	int		res;
	int		p;

	p = 0;
	res = 0;
	va_start(args, format);
	while (format[p] != '\0')
	{
		if (format[p] == '%')
		{
			p++;
			res = assig_ft(format, &res, &p, args);
		}
		else
			res += ft_putchar(format[p]);
		p++;
	}
	va_end(args);
	return (res);
}
/*int	main(void)
{
	int i = printf("  %s \n", NULL);
	int p = ft_printf("  %s \n", NULL);
	printf("%i\n",i);
	printf("%i\n",p);

	return (0);
}*/