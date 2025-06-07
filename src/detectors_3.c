/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detectors_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:14:28 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/07 22:15:00 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	dir_exists(const char *filepath)
{
	int		i;
	char	*dir;
	int		ret;

	// Busca la última '/' (si hay)
	i = ft_strlen(filepath);
	while (i >= 0 && filepath[i] != '/')
		i--;

	// Si no hay '/', el archivo está en el cwd => directorio existe
	if (i <= 0)
		return (1);

	// Crea una copia del path solo con la parte del directorio
	dir = ft_strndup(filepath, i);
	if (!dir)
		return (0);

	// Verifica si el directorio existe
	ret = (access(dir, F_OK | W_OK) == 0);
	free(dir);
	return (ret);
}