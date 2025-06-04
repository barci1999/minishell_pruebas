/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:04:44 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/04 19:09:05 by pablalva         ###   ########.fr       */
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
void evalue_next_char(char *src, int *i, int *m, char **result)
{
	(void)result;
    if (src[*i + 1])
    {
        if (ft_is_space(src[*i + 1]) || is_char_redirect(src[*i + 1]) || is_quote(src[*i + 1]))
        {
            (*m)++;  // Empezamos una nueva palabra en el próximo ciclo
        }
    }
    else
    {
        (*m)++;  // Fin del string, avanzar a próxima posición
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

void	doble_quote(char *src, char **result, int *i,t_mini *mini)
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
			*result = ft_free_strjoin(*result, temp);
			if (src[*i] == '\"')
				break ;
		}
		else
			*result = add_chr_to_str(*result, src[*i]);
		(*i)++;
	}
}

void	no_quote(char *src, char **result,int *i, t_mini *mini, int *m)
{
	char	*temp;

	temp = NULL;
	if (src[*i] == '$')
	{
		(*i)++;
		temp = take_the_expand(src, i,mini);
		*result = ft_free_strjoin(src, temp);
	}
	if(is_char_redirect(src[*i]))
	{	
		result[*m] = NULL;
		*result = add_chr_to_str(result[*m], src[*i]);
		if (src[*i + 1] && is_char_redirect(src[*i + 1]))
		{
			(*i)++;
			*result = add_chr_to_str(result[*m], src[*i]);
		}
		if(!ft_is_space(src[*i+1]))
			(*m)++;
		return ;
	}
	*result = add_chr_to_str(*result, src[*i]);
}
char	**fukking_quotes(char *src,t_mini *mini)
{
	int		i;
	int		m;
	char	**result;
	size_t j = 0;

	i = 0;
	m = 0;
	result = malloc((number_of_cmd_arg(src) + 1) * sizeof(char *));
	while (j <= number_of_cmd_arg(src))
	{
		result[j++] = NULL;
	}
	while (src[i])
	{
		if(ft_is_space(src[i]))
			i++;
		if (src[i] == '\'')
			single_quote(&result[m], &i, src);
		else if (src[i] == '\"')
			doble_quote(src,&result[m],&i,mini);
		else if (src[i] != '\'' && src[i] != '\"' )
		{
			no_quote(src,&result[m],&i,mini, &m);
		}
		evalue_next_char(src, &i, &m, &result[m]);
		i++;
	}
	for(int j = 0;result[j];j++)
		printf("%s\n",result[j]);
	return (result);
}
