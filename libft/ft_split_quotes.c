/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:41:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/26 14:02:42 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_pipes(char *input, char c)
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

static void	modifi_quote(char *input, char *quote, int j)
{
	if (input[j] == '\'' || input[j] == '\"')
	{
		if (!*quote)
			*quote = input[j];
		else if (*quote == input[j])
			*quote = 0;
	}
}

static int	last_assign(t_split *data, char *input)
{
	if (data->j > data->i)
	{
		data->res[data->r] = ft_substr(input, data->i, (data->j - data->i));
		if (!data->res[data->r])
		{
			ft_free_mat(data->res);
			return (1);
		}
		data->r++;
	}
	return (0);
}

char	**ft_split_quotes(char *input, char c)
{
	t_split	data;

	data.i = 0;
	data.j = 0;
	data.r = 0;
	data.quote = 0;
	data.res = malloc((num_pipes(input, c) + 2) * sizeof(char *));
	if (!data.res)
		return (NULL);
	while (input[data.j])
	{
		modifi_quote(input, &data.quote, data.j++);
		if (input[data.j] == c && !data.quote)
		{
			data.res[data.r] = ft_substr(input, data.i, (data.j - data.i));
			if (!data.res[data.r])
				return (ft_free_mat(data.res), NULL);
			data.r++;
			data.i = data.j + 1;
		}
	}
	if (last_assign(&data, input))
		return (ft_free_mat(data.res), NULL);
	return (data.res[data.r] = NULL, data.res);
}
// int main(void)
// {
// 	char *src = "";
// 	char **res = split_pipes(src,' ');
// 	int i = 0;
// 	int j = 0;
// 	while (res[i])
// 	{
// 		while (res[i][j])
// 		{
// 			if(res[i][j] == ' ')
// 				write(1,"=",1);
// 			else
// 				write(1,&res[i][j],1);
// 			j++;
// 		}
// 		j = 0;
// 		write(1,"\n",1);
// 		i++;
// 	}
// 	if(res)
// 		ft_free_mat(res);
// 	return(0);
// }
