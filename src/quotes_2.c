/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:04:44 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/03 22:20:19 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

char	*ft_free_strjoin(char *s1, char *s2)
{
	int		size_s1;
	int		size_s2;
	char	*str;
	int		i;
	int		j;

	size_s1 = ft_get_strlen(s1);
	size_s2 = ft_get_strlen(s2);
	str = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < size_s1)
		str[i++] = s1[j++];
	j = 0;
	while (j < size_s2)
		str[i++] = s2[j++];
	str[i] = '\0';
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (str);
}
int is_char_redirect(char c)
{
	if(c == '<' || c == '>')
		return(1);
	return(0);
}
char	*take_the_expand(char *src, int *i, t_mini *mini)
{
	char	*temp;
	char	*temp_2;

	temp = NULL;
	temp_2 = NULL;
	while (src[*i] && (ft_isalnum(src[*i]) || src[*i] == '_'))
	{
		temp = add_chr_to_str(temp, src[*i]);
		(*i)++;
	}
	temp_2 = get_env_value(mini, temp);
	return (temp_2);
}
void	evalue_next_char(char *src, int *i, int *m, char *result)
{
	if (src[*i + 1])
	{
		if (ft_is_space(src[*i + 1]))
		{
			(*m)++;
			return ;
		}
		else if (is_char_redirect(src[*i + 1]))
		{
			(*m)++;
			if (src[*i + 2] && is_char_redirect(src[*i + 2]))
			{
				result = add_chr_to_str(result, src[*i + 1]);
				result = add_chr_to_str(result, src[*i + 2]);
				(*m)++;
			}
			else
			{
				result = add_chr_to_str(result, src[*i + 1]);
				(*m)++;
			}
		}
		else
			return ;
	}
}

void	single_quote(char *result, int *i, char *src)
{
	if (!src[*i + 1])
		return ;
	else
		(*i)++;
	while (src[*i] != '\'')
	{
		result = add_chr_to_str(result, src[*i]);
		(*i)++;
	}
}

void	doble_quote(char *src, char *result, int *i,t_mini *mini)
{
	char	*temp;

	if (!src[*i + 1])
		return ;
	else
		(*i)++;
	while (src[*i] != '\"')
	{
		if (src[*i + 1] && src[*i] == '$')
		{
			(*i)++;
			temp = take_the_expand(src, i,mini);
			result = ft_free_strjoin(result, temp);
			if (src[*i] == '\"')
				break ;
		}
		else
			add_chr_to_str(result, src[*i]);
		(*i)++;
	}
}

void	no_quote(char *src, char *result,int *i, t_mini *mini)
{
	char	*temp;

	temp = NULL;
	if (src[*i] == '$')
	{
		(*i)++;
		temp = take_the_expand(src, i,mini);
		result = ft_free_strjoin(src, temp);
	}
	else
		add_chr_to_str(src, src[*i]);
	if (src[*i + 1])
	{
		if (is_quote(src[*i + 1] || is_char_redirect(src[*i + 1])))
			return ;
	}
}
char	**fukking_quotes(char *src,t_mini *mini)
{
	int		i;
	int		m;
	char	**result;

	i = 0;
	m = 0;
	result = NULL;
	while (src[i])
	{
		while (ft_is_space(src[i]))
			i++;
		if (src[i] == '\'')
		{
			single_quote(result[m], &i, src);
			evalue_next_char(src, &i, &m, result[m]);
		}
		else if (src[i] == '\"')
		{
			doble_quote(src,result[m],&i,mini);
			evalue_next_char(src, &i, &m, result[m]);
		}
		else if (src[i] != '\'' && src[i] != '\"')
		{
			no_quote(src,result[m],&i,mini);
			evalue_next_char(src, &i, &m, result[m]);
		}
		i++;
	}
	return (result);
}
