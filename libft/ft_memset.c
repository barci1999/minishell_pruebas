/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:52:48 by pablalva          #+#    #+#             */
/*   Updated: 2024/09/26 17:52:11 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*p;
	unsigned char	value;

	p = (unsigned char *)s;
	value = (unsigned char)c;
	while (n--)
	{
		*p++ = value;
	}
	return (s);
}
/*int	main(void)
{
	char	s[50] = "cocacola";
	int	c = '1';
	int	n = 3;
	printf("%s",ft_memset(s,c,n));
}*/
