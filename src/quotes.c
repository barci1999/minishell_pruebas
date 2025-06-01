/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:35:23 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/01 21:53:22 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

char	*add_chr_to_str(char *src, char c)
{
	char	*result;
	int		len;
	int		i;

	len = 0;
	i = 0;
	if (src != NULL)
		len = ft_strlen(src);
	result = malloc((len + 2) * sizeof(char));
	if (result == NULL)
		return (NULL);
	while (i < len)
	{
		result[i] = src[i];
		i++;
	}
	result[i++] = c;
	result[i] = '\0';
	if (src)
		free(src);
	return (result);
}

void	in_double_quote(char *src, int *i, char ***matrix, int m, t_mini *mini)
{
	char	*temp;

	temp = NULL;
	while (src[*i] == '\"')
		(*i)++;
	while (src[*i])
	{
		if (src[*i] == '\"' || ft_is_space(src[*i] || src[*i] == '\0'))
		{
			if (is_quote(src[*i]) || ft_is_space(src[*i]))
				(*i)++;
			break ;
		}
		else if (src[*i] == '$' && src[*i + 1])
		{
			(*i)++;
			temp = add_expand_str(mini, src, matrix[0][m], i);
		}
		else
			temp = add_chr_to_str(matrix[0][m], src[*i]);
		matrix[0][m] = ft_strdup(temp);
		free(temp);
		(*i)++;
	}
}

void	in_single_quote(char *src, int *i, char ***matrix, int m)
{
	char	*temp;

	temp = NULL;
	while (src[*i] == '\'')
		(*i)++;
	while (src[*i])
	{
		if (src[*i] == '\'' || ft_is_space(src[*i] || src[*i] == '\0'))
		{
			if (is_quote(src[*i]) || ft_is_space(src[*i]))
				(*i)++;
			break ;
		}
		temp = add_chr_to_str(matrix[0][m], src[*i]);
		matrix[0][m] = ft_strdup(temp);
		free(temp);
		(*i)++;
	}
}

void	no_quote(char *src, int *i, char ***matrix, size_t *m, t_mini *mini)
{
	char	*temp;

	temp = NULL;
	while (src[*i])
	{
		if (is_quote(src[*i]) || ft_is_space(src[*i]))
			break ;
		if (src[*i] == '>' || src[*i] == '<')
		{
			if (temp && ft_strlen(temp) > 0)
			{
				matrix[0][*m] = ft_strdup(temp);
				free(temp);
				temp = NULL;
				(*m)++;
			}
			if (src[*i + 1] == src[*i])
			{
				matrix[0][*m] = malloc(3);
				matrix[0][*m][0] = src[*i];
				matrix[0][*m][1] = src[*i];
				matrix[0][*m][2] = '\0';
				(*i) += 2;
			}
			else
			{
				matrix[0][*m] = malloc(2);
				matrix[0][*m][0] = src[*i];
				matrix[0][*m][1] = '\0';
				(*i)++;
			}
			(*m)++;
			return ;
		}
		else if (src[*i] == '$' && src[*i + 1])
		{
			(*i)++;
			temp = add_expand_str(mini, src, temp, i);
		}
		else
		{
			temp = add_chr_to_str(temp, src[*i]);
			(*i)++;
		}
	}
	if (temp && ft_strlen(temp) > 0)
	{
		matrix[0][*m] = ft_strdup(temp);
		free(temp);
		(*m)++;
	}
}

char	**take_the_arg(char *src, t_mini *mini)
{
	int		i;
	size_t	m;
	char	**matrix;
	size_t j;
	j = 0;
	i = 0;
	m = 0;
	matrix = malloc((number_of_cmd_arg(src) + 1) * sizeof(char *));
	if (!matrix)
		return (NULL);
	while (j >= number_of_cmd_arg(src))
		matrix[j++] = NULL;
	while (src[i])
	{
		while (src[i] && ft_is_space(src[i]))
			i++;
		if (src[i] == '\'')
			in_single_quote(src, &i, &matrix, m++);
		else if (src[i] == '"')
			in_double_quote(src, &i, &matrix, m++, mini);
		else if (src[i])
			no_quote(src, &i, &matrix, &m, mini);
		while (src[i] && ft_is_space(src[i]))
			i++;
	}
	matrix[m] = NULL;
	return (matrix);
}
