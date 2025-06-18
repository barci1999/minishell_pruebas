/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detectors_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 22:14:28 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 15:23:48 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dir_exists(const char *filepath)
{
	int		i;
	char	*dir;
	int		ret;

	i = ft_strlen(filepath);
	while (i >= 0 && filepath[i] != '/')
		i--;
	if (i <= 0)
		return (1);
	dir = ft_strndup(filepath, i);
	if (!dir)
		return (0);
	ret = (access(dir, F_OK | W_OK) == 0);
	free(dir);
	return (ret);
}

int	is_operator_char(char c)
{
	return (c == '>' || c == '<');
}
