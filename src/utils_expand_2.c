/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:20:50 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/12 15:19:55 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*expand_var(char *input, size_t i, size_t j)
{
	char	*name_var;
	char	*exp_var;
	char	*rest;
	size_t	t;
	size_t	e;

	e = 0;
	name_var = NULL;
	exp_var = NULL;
	rest = NULL;
	t = 0;
	while (!is_space(input[j]) && input[j] != '\"' && input[j])
		j++;
	if (input[j] == '\0' && input[j - 1] == '\"')
		j--;
	name_var = ft_substr(input, i, (j - i));
	if (!name_var)
	{
		/*gestion de leaks*/
	}
	exp_var = ft_strjoin("VAR_", getenv(name_var));
	if (!exp_var)
	{
		/* gestion de leaks y usar env propio*/
	}
	if (input[j])
	{
		rest = ft_substr(input, j, ft_strlen(input));
		if (!rest)
		{
			/*gestion de leaks */
		}
	}
	else
		return (ft_strjoin(exp_var, NULL));
	return (ft_strjoin(exp_var, rest));
}

char	*expand_str(char *input)
{
	size_t	i;
	size_t	j;
	char	*pre_exp;
	char	*rest;
	char	*result;

	i = 0;
	j = 0;
	pre_exp = NULL;
	rest = NULL;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'' && input[i])
			{
				i++;
			}
		}
		else if (input[i] == '$')
		{
			j = i;
			pre_exp = ft_substr(input, 0, j);
			if (!pre_exp)
			{
				/* gestion de leacks */
			}
			rest = expand_var(input, i + 1, j);
			if (!rest)
			{
				/*gestion de leacks */
			}
			free(input);
			input = ft_strjoin(pre_exp, rest);
			if (!input)
			{
				/* gestion de leaks */
			}
		}
		if (input[i] != '\0')
			i++;
	}
	result = rem_sin_quotes(input);
	return (input);
}
size_t	nb_of_quotes(char *input)
{
	size_t	quotes;
	int		i;

	quotes = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
		{
			quotes++;
		}
		i++;
	}
	return (quotes);
}
char	*rem_sin_quotes(char *input)
{
	size_t	nb_quotes;
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	nb_quotes = nb_of_quotes(input);
	result = malloc((ft_strlen(input) - nb_quotes + 1) * sizeof(char));
	if (!result)
	{
		/* gestion de leaks */
	}
	while (input[i])
	{
		if (input[i] != '\'')
		{
			result[j] = input[i];
			j++;
			i++;
		}
		else
			i++;
	}
	result[j] = '\0';
	return (result);
}
