/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:49:58 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:50:48 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(214748364, fd);
		ft_putchar_fd('8', fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	ft_putchar_fd((n % 10) + '0', fd);
}
/*int main(void)
{
	int fd;

	Abrir un archivo llamado "numeros.txt" en modo escritura (crear si no existe)
	fd = open("numeros.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)  // Verificar si el archivo se abrió correctamente
	{
		write(2, "Error al abrir el archivo\n", 26);
		return (1);  // Código de error si falló
	}

	// Escribir algunos números en el archivo
	ft_putnbr_fd(42, fd);         // Escribe "42"
	ft_putchar_fd('\n', fd);      // Escribe salto de línea
	ft_putnbr_fd(-12345, fd);     // Escribe "-12345"
	ft_putchar_fd('\n', fd);      // Escribe salto de línea
	ft_putnbr_fd(-2147483648, fd); // Escribe el máximo valor de un int
	ft_putchar_fd('\n', fd);      // Escribe salto de línea

	close(fd);  // Cerrar el archivo

	return (0);
}*/