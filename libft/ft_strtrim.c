/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:27 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:59:01 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	right_to_left(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while ((s1[i] != '\0') && (set[j] != '\0'))
	{
		j = 0;
		while ((s1[i] != set[j]) && (set[j] != '\0'))
			j++;
		i++;
	}
	return (i);
}

unsigned int	left_to_right(const char *s1, const char *set)
{
	unsigned int	p;
	unsigned int	j;

	p = ft_strlen(s1);
	j = 0;
	while ((p != 0) && (set[j] != '\0'))
	{
		j = 0;
		while ((s1[p - 1] != set[j]) && (set[j] != '\0'))
		{
			j++;
		}
		if (set[j] != '\0')
			p--;
	}
	return (p);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	p;
	unsigned int	i;
	char			*s2;

	i = right_to_left(s1, set);
	p = left_to_right(s1, set);
	if ((i <= p) && (i != 0))
		s2 = ft_substr(s1, (i - 1), (p - i + 1));
	else if (*set == '\0')
		return (ft_strdup(s1));
	else
		s2 = ft_calloc(1, sizeof(char));
	return (s2);
}
/*int	main(void)
{
	const char *s1 = "hola";
	const char *set = "";
	printf("%s", ft_strtrim(s1, set));
	return (0);
}*/