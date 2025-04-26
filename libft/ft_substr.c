/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:55:27 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/26 21:13:38 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*d_less_len(char *dest, const char *s, unsigned int start,
		size_t len)
{
	size_t	d;

	d = 0;
	while (d < len)
	{
		dest[d] = s[start + d];
		d++;
	}
	dest[d] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		dest = malloc(1 * sizeof(char));
		if (dest == NULL)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	dest = malloc((len + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	d_less_len(dest, s, start, len);
	return (dest);
}
/*int main(void)
{
	const   char s[] ="hello, world";
	unsigned    int start = 0;
	size_t len = 1;
	printf("%s\n",ft_substr(s, start, len));
	return(0);
}*/