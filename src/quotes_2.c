/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:04:44 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/13 19:41:50 by ksudyn           ###   ########.fr       */
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
		if (src[*i + 1] && ft_is_space(src[*i + 1]))
			(*i)++;
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

static void	parse_quotes_loop(t_quotes *quot, t_mini *mini)
{
	while (quot->src[*quot->i])
	{
		while (ft_is_space(quot->src[*quot->i]))
			(*quot->i)++;
		quot->result = &quot->result_base[*quot->m];
		if (quot->src[*quot->i] == '\'')
			single_quote(quot);
		else if (quot->src[*quot->i] == '\"')
			doble_quote(quot, mini);
		else
			no_quote(quot, mini);
		evalue_next_char(quot);
		(*quot->i)++;
	}
}

char	**fukking_quotes(char *src, t_mini *mini)
{
	t_quotes	quot;
	char		**result;
	size_t		j;
	int			i;
	int			m;

	i = 0;
	m = 0;
	j = 0;
	result = malloc((number_of_cmd_arg(src) + 1) * sizeof(char *));
	while (j <= number_of_cmd_arg(src))
		result[j++] = NULL;
	quot.src = src;
	quot.i = &i;
	quot.m = &m;
	quot.result_base = result;
	parse_quotes_loop(&quot, mini);
	return (result);
}
