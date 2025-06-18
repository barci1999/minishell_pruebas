/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:27:21 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 22:28:18 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	nb_redirrec(char **mat)
{
	int		i;
	size_t	result;

	i = -1;
	result = 0;
	while (mat[++i])
	{
		if (ft_strcmp(mat[i], ">") == 0 || ft_strcmp(mat[i], ">>") == 0
			|| ft_strcmp(mat[i], "<") == 0 || ft_strcmp(mat[i], "<<") == 0)
			result++;
	}
	return (result);
}

size_t	num_pipes(char *input, char c)
{
	size_t	count;
	char	quote;
	int		i;

	count = 0;
	quote = 0;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"'))
		{
			if (!quote)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		else if (input[i] == c && !quote)
			count++;
		i++;
	}
	return (count);
}
