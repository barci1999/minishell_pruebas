/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:55:27 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 13:56:28 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	mem;

	mem = len;
	if (ft_strlen(s) <= start)
		return (ft_calloc(1, 1));
	if (mem > ft_strlen(s + start))
		mem = ft_strlen(s + start);
	sub = ft_calloc(mem + 1, 1);
	if (sub == 0)
		return (0);
	ft_strlcpy(sub, &s[start], mem + 1);
	return (sub);
}
/*int main(void)
{
	const   char s[] ="hello, world";
	unsigned    int start = 0;
	size_t len = 1;
	printf("%s\n",ft_substr(s, start, len));
	return(0);
}*/