/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 16:35:23 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/04 18:01:57 by pablalva         ###   ########.fr       */
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

// void	in_double_quote(char *src, int *i, char ***matrix, int *m, t_mini *mini)
// {
// 	char	*temp;

// 	temp = NULL;
// 	while (src[*i] == '\"')
// 		(*i)++;
// 	while (src[*i])
// 	{
// 		if (src[*i] == '\"' || ft_is_space(src[*i] || src[*i] == '\0'))
// 		{
// 			if ((src[*i+1]))
// 			{
// 				if(ft_is_space(src[*i+1]))
// 				{
// 					(*m)++;
// 					break ;
// 				}
// 			}
// 		}
// 		else if (src[*i] == '$' && src[*i + 1])
// 		{
// 			(*i)++;
			
// 			printf("%s\n",matrix[0][*m]);
// 			temp = add_expand_str(mini, src, matrix[0][*m], i);
// 			(*i)++;
// 		}
// 		else
// 		{
// 			temp = add_chr_to_str(matrix[0][*m], src[*i]);
// 		}
// 		matrix[0][*m] = ft_strdup(temp);
// 		if(!temp)
// 			free(temp);
// 		if(src[*i + 1] == ' ')
// 		{
// 			(*m)++;
// 			break;
// 		}
// 		(*i)++;
// 	}
// }

// void	in_single_quote(char *src, int *i, char ***matrix, int *m)
// {
// 	char	*temp;

// 	temp = NULL;
// 	while (src[*i] == '\'')
// 		(*i)++;
// 	while (src[*i])
// 	{
// 		if (src[*i] == '\'' || ft_is_space(src[*i]) || src[*i] == '\0')
// 		{
// 			if ((src[*i+1]))
// 			{
// 				if(ft_is_space(src[*i+1]))
// 					(*m)++;
// 			}
// 			break ;
// 		}
// 		temp = add_chr_to_str(matrix[0][*m], src[*i]);
// 		matrix[0][*m] = ft_strdup(temp);
// 		printf("%s\n",matrix[0][*m]);
// 		free(temp);
// 		(*i)++;
// 	}
// }

// void	no_quote(char *src, int *i, char ***matrix, int *m, t_mini *mini)
// {
// 	char	*temp;

// 	temp = NULL;
// 	while (src[*i])
// 	{
// 		if (is_quote(src[*i]) || ft_is_space(src[*i]))
// 		{
// 			break ;
// 		}
// 		if (src[*i] == '>' || src[*i] == '<')
// 		{
// 			if (temp && ft_strlen(temp) > 0)
// 			{
// 				matrix[0][*m] = ft_strdup(temp);
// 				free(temp);
// 				temp = NULL;
// 				(*m)++;
// 			}
// 			if (src[*i + 1] == src[*i])
// 			{
// 				matrix[0][*m] = malloc(3);
// 				matrix[0][*m][0] = src[*i];
// 				matrix[0][*m][1] = src[*i];
// 				matrix[0][*m][2] = '\0';
// 				(*i) += 2;
// 			}
// 			else
// 			{
// 				matrix[0][*m] = malloc(2);
// 				matrix[0][*m][0] = src[*i];
// 				matrix[0][*m][1] = '\0';
// 				(*i)++;
// 			}
// 			(*m)++;
// 			return ;
// 		}
// 		else if (src[*i] == '$' && src[*i + 1])
// 		{
// 			(*i)++;
// 			temp = add_expand_str(mini, src, temp, i);
// 			(*i)++;
// 		}
// 		else
// 		{
// 			temp = add_chr_to_str(temp, src[*i]);
// 			(*i)++;
// 		}
// 	}
// 	if (temp && ft_strlen(temp) > 0)
// 	{
// 		matrix[0][*m] = ft_strdup(temp);
// 		free(temp);
// 		(*m)++;
// 	}
// }

// char	**take_the_arg(char *src, t_mini *mini)
// {
// 	int		i;
// 	int	m;
// 	char	**matrix;
// 	matrix = NULL;
// 	size_t j;
// 	j = 0;
// 	i = 0;
// 	m = 0;
// 	matrix = malloc((number_of_cmd_arg(src) + 1) * sizeof(char *));
// 	if (!matrix)
// 		return (NULL);
// 	while (j <= number_of_cmd_arg(src))
// 		matrix[j++] = NULL;
// 	while (src  && src[i])
// 	{
// 		while (src[i] && ft_is_space(src[i]))
// 		{
// 			i++;
// 		}
// 		if (src[i] == '\'')
// 		{
// 			in_single_quote(src, &i, &matrix, &m);
// 			i++;
// 		}
// 		else if (src[i] == '"')
// 		{
// 			in_double_quote(src, &i, &matrix, &m, mini);
// 			i++;
// 		}
// 		else if (src[i])
// 		{
// 			no_quote(src, &i, &matrix, &m, mini);
// 		}
// 	}
// 	return (matrix);
// }
