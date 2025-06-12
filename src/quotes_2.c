/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:04:44 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/12 20:30:07 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*take_the_expand(char *src, int *i, t_mini *mini)
{
	char	*temp;
	char	*temp_2;
	char	*value;

	temp = NULL;
	temp_2 = NULL;
	if (src[*i] == '?')
	{
		temp_2 = ft_itoa(g_exit_status);
		return (temp_2);
	}
	while (src[*i] && (ft_isalnum(src[*i]) || src[*i] == '_'))
	{
		temp = add_chr_to_str(temp, src[*i]);
		(*i)++;
	}
	value = get_env_value(mini, temp);
	if (value == NULL)
		temp_2 = ft_strdup("");
	else
		temp_2 = ft_strdup(value);
	free(temp);
	return (temp_2);
}

void	evalue_next_char(char *src, int *i, int *m, char **result)
{
	(void)result;
	if (src[*i + 1])
	{
		if (ft_is_space(src[*i + 1]) || is_operator_char(src[*i + 1]))
		{
			(*m)++;
		}
	}
	else
	{
		(*m)++;
	}
}

void	single_quote(char **result, int *i, char *src)
{
	if (!src[*i + 1])
		return ;
	else
		(*i)++;
	while (src[*i] != '\'')
	{
		*result = add_chr_to_str(*result, src[*i]);
		(*i)++;
	}
}

void	doble_quote(char *src, char **result, int *i, t_mini *mini)
{
	char	*temp;

	if (!src[*i + 1])
		return ;
	else
		(*i)++;
	while (src[*i] != '\"')
	{
		if (src[*i + 1] && src[*i] == '$' && (ft_isalnum(src[*i + 1])
				|| src[*i + 1] == '_'))
		{
			(*i)++;
			temp = take_the_expand(src, i, mini);
			*result = ft_free_strjoin(*result, temp);
			if (src[*i] == '\"')
				break ;
			//(*i)++;
		}
		else
			*result = add_chr_to_str(*result, src[*i]);
		(*i)++;
	}
}

void	no_quote(char *src, char **result, int *i, t_mini *mini, int *m)
{
	char	*temp;

	temp = NULL;
	if (src[*i + 1] && src[*i] == '$')
	{
		(*i)++;
		temp = take_the_expand(src, i, mini);
		*result = ft_free_strjoin(*result, temp);
		return ;
	}
	if (is_operator_char(src[*i]))
	{
		//printf("%i\n",*m);
		*result = NULL;
		*result = add_chr_to_str(*result, src[*i]);
		if (src[*i + 1] && is_operator_char(src[*i + 1]))
		{
			(*i)++;
			*result = add_chr_to_str(*result, src[*i]);
		}
		if (!ft_is_space(src[*i + 1]))
		{
			//(*i)++;
			(*m)++;
		}
		return ;
	}
	*result = add_chr_to_str(*result, src[*i]);
}

char	**fukking_quotes(char *src, t_mini *mini)
{
	int		i;
	int		m;
	char	**result;
	size_t	j;

	j = 0;
	i = 0;
	m = 0;
	result = malloc((number_of_cmd_arg(src) + 1) * sizeof(char *));
	while (j <= number_of_cmd_arg(src))
	{
		result[j++] = NULL;
	}
	while (src[i])
	{
		while (ft_is_space(src[i]))
			i++;
		if (src[i] == '\'')
			single_quote(&result[m], &i, src);
		else if (src[i] == '\"')
		{
			doble_quote(src, &result[m], &i, mini);
		}
		else if (src[i] != '\'' && src[i] != '\"')
		{
			no_quote(src, &result[m], &i, mini, &m);
		}
		evalue_next_char(src, &i, &m, &result[m]);
		i++;
	}
	return (result);
}
