/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:37:14 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/07 19:25:57 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static char	**ft_free(char **splt)
{
	int	i;

	i = 0;
	while (splt && splt[i])
	{
		free (splt[i]);
		i++;
	}
	free (splt);
	return (NULL);
}

static int	ft_wordcount(char const *s, char c)
{
	int	i;
	int	w;
	int	f;

	i = 0;
	w = 0;
	f = 0;
	while (s[i])
	{
		if (s[i] != c && f == 0)
		{
			w++;
			f = 1;
		}
		else if (s[i] == c && f == 1)
			f = 0;
		i++;
	}
	return (w);
}

static int	ft_length(char const *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i] != c && s[i])
	{
		n++;
		i++;
	}
	return (n);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		w;
	char	*w_len;
	char	**splt;

	w = ft_wordcount(s, c);
	i = 0;
	w_len = (char *)s;
	splt = ft_calloc(w + 1, 8);
	if (splt == 0)
		return (ft_free((splt)));
	while (i < w)
	{
		while (*w_len == c)
			w_len++;
		splt[i] = ft_calloc(ft_length(w_len, c) + 1, 1);
		if (splt[i] == 0)
			return (ft_free(splt));
		ft_strlcpy(splt[i], w_len, ft_length(w_len, c) + 1);
		while (*w_len && *w_len != c)
			w_len++;
		i++;
	}
	return (splt);
}
