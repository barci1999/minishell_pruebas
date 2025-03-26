/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-25 19:48:04 by pablalva          #+#    #+#             */
/*   Updated: 2025-03-25 19:48:04 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pruebas.h"

static int is_space(char c)
{
	if(c == 32 || (c >= 9 && c <= 13))
		return(1);
	return(0);
}
char	*expand_var(char *input)
{
	char	*dollar_var_name = NULL;
	char	*expanded_var = NULL;
	char	*result = NULL;
	int		v;
	int		i;
	int r = 0;
	v = 0;
	i = 0;
	dollar_var_name = take_dollar(input);
	if (!dollar_var_name)
		return (NULL);
	expanded_var = getenv(dollar_var_name);
	result = malloc((ft_strlen(input) + ft_strlen(expanded_var)
				- ft_strlen(dollar_var_name) + 1) * sizeof(char));
	if (!result)
	{
		free(dollar_var_name);
		free(expanded_var);
		return (NULL);
	}
	while (input[i])
	{
		if (input && input[i] != '$')
		{
			while(input && input[i] != '$')
			{
				result[r]= input[i];
				i++;
				r++;
			}
		}
		if (input[i] == '$')
		{
			while (expanded_var[v])
			{
				result[r] = expanded_var[v];
				r++;
				v++;
			}
			i += ft_strlen(dollar_var_name) + 1;
			while(input[i])
			{
				result[r] = input[i];
				i++;
				r++;
			}
			result[r] = '\0';
			return(result);
		}
	}
	result[r] = '\0';
	return(result);
}
int	number_of_dollar(char *input)
{
	int	i;
	int	dollar;

	i = 0;
	dollar = 0;
	while (input[i])
	{
		if (input[i] == '$')
			dollar++;
		i++;
	}
	return (dollar);
}
char	*take_dollar(char *input)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] != '$')
		{
			i++;
			j++;
		}
		if (input[i] == '$')
		{
			j++;
			while (!is_space(input[i]))
			{
				i++;
			}
			result = ft_substr(input, j, (i - j));
			if (!result)
				return (NULL);
			return (result);
		}
	}
	return (NULL);
}