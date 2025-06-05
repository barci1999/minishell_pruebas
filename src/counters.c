/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:27:21 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/05 15:12:04 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

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

static bool	analize_nbr(int *double_quote, int *single_quote)
{
	if (*double_quote % 2 == 0 && *single_quote % 2 == 0)
		return (true);
	else if (*double_quote == 0 && *single_quote % 2 == 0)
		return (true);
	else if (*double_quote % 2 == 0 && *single_quote == 0)
		return (true);
	else
		return (false);
}

bool	nbr_quotes_ok(char *src)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (src[i])
	{
		if (src[i] == '\"')
		{
			double_quote++;
			i++;
			while (src[i] && src[i] != '\"')
				i++;
			if (src[i] == '\"')
			{
				double_quote++;
				i++;
			}
		}
		else if (src[i] == '\'')
		{
			single_quote++;
			i++;
			while (src[i] && src[i] != '\'')
				i++;
			if (src[i] == '\'')
			{
				single_quote++;
				i++;
			}
		}
		else
			i++;
	}
	return (analize_nbr(&double_quote, &single_quote));
}
