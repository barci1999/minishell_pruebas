/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 12:34:51 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/09 15:46:41 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(char const *format, ...);
int		ft_putchar(int c);
int		ft_putstr(const char *s);
int		ft_putnbr(int nb);
int		ft_putnbrnu(unsigned int nb);
size_t	ft_strlen(const char *s);
int		ft_pointer_hex(unsigned long long nb, char *base, int flag);
int		ft_hexadec(unsigned int nb, char *base);

#endif