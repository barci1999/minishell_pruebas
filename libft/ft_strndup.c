/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:04:51 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/31 16:11:25 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t len)
{
	char	*dest;
	char	*start;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	dest = (char *)malloc(len + 1);
	if (dest == NULL)
		return (NULL);
	start = dest;
	while (i < len && s[i] != '\0')
	{
		*dest++ = s[i];
		i++;
	}
	*dest = '\0';
	return (start);
}
