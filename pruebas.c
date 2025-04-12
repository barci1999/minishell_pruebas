/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:43:13 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/12 19:09:46 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

size_t	num_pipes(char *input)
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
		else if (input[i] == '|' && !quote)
			count++;
		i++;
	}
	return (count);
}

void	modifi_quote(char *input, char *quote, int j)
{
	if (input[j] == '\'' || input[j] == '\"')
	{
		if (!*quote)
			*quote = input[j];
		else if (*quote == input[j])
			*quote = 0;
	}
}

char	**split_pipes(char *input)
{
	char	**result;
	int		r;
	int		i;
	int		j;
	char	quote;

	r = 0;
	i = 0;
	j = 0;
	quote = 0;
	result = malloc((num_pipes(input) + 2) * sizeof(char *));
	printf("%zu\n",num_pipes(input));
	while (input[j])
	{
		modifi_quote(input, &quote, j);
		if (input[j] == '|' && !quote)
		{
			result[r++] = ft_substr(input, i, (j - i));
			r++;
			i = j + 1;
		}
		j++;
	}
	if (j > i)
	{
		result[r++] = ft_substr(input, i, j - i);
		r++;
		ft_printf("%s\n",result[r]);
	}
	result[r] = NULL;
	return (result);
}
