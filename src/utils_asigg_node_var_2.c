/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_asigg_node_var_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:11:10 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/19 19:17:09 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_perror_exit(char *msg, int code)
{
	perror(msg);
	g_exit_status = code;
	exit(code);
}

t_status_type	safe_add_str(char ***mat, char *str)
{
	*mat = add_str_to_mat(*mat, str);
	if (!*mat)
		return (MALLOC_ERROR);
	return (OK);
}

void	print_error(char *cmd, char *msg, int code)
{
	if (cmd)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	g_exit_status = code;
}

void	print_error_exit(char *cmd, char *msg, int code)
{
	if (cmd)
	{
		write(2, "minishell: ", 11);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	g_exit_status = code;
	exit(code);
}

char	**add_str_to_mat(char **src, char *to_add)
{
	char	**result;
	int		i;

	i = 0;
	result = malloc((ft_matlen(src) + 2) * sizeof(char *));
	if (!result)
		return (ft_free_mat(src), NULL);
	ft_bzero(result, (ft_matlen(src) + 2) * sizeof(char *));
	while (src && src[i])
	{
		result[i] = ft_strdup(src[i]);
		if (!result[i])
			return (ft_free_mat(result), ft_free_mat(src), NULL);
		i++;
	}
	result[i] = ft_strdup(to_add);
	if (!result[i])
		return (ft_free_mat(result), ft_free_mat(src), NULL);
	result[i + 1] = NULL;
	return (ft_free_mat(src), result);
}
