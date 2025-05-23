/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 10:19:18 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/11 13:06:16 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char			*cpy;
	unsigned long	n;

	if (s1 == NULL)
		return (NULL);
	n = ft_strlen(s1);
	cpy = (char *)malloc(n + 1);
	if (!cpy)
		return (NULL);
	ft_strlcpy(cpy, s1, n + 1);
	return (cpy);
}
/*int main(void)
{
	const char s[20] = "cocacola";
	ft_strdup(s);
	printf("%s",dest);
	free(dest);
	return (0);
}*/