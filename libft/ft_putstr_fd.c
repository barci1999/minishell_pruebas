/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 11:32:22 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:50:53 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
/*int	main(void)
{
	int	fd;
	char *str = "Hola, mundo!\n";

	// Abrir el archivo "salida.txt" en modo escritura y crear si no existe.
	fd = open("salida.txt", O_WRONLY | O_CREAT, 0644);
	if (fd == -1)  // Verificar si se abrió correctamente
	{
		write(2, "Error al abrir el archivo\n", 26);
		return (1);  // Salir del programa con código de error
	}

	ft_putstr_fd(str, fd);  // Escribir la cadena "Hola, mundo!" en el archivo

	close(fd);  // Cerrar el archivo
	return (0);
}*/