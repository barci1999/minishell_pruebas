/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:25:46 by pablalva          #+#    #+#             */
/*   Updated: 2024/09/26 17:51:19 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n--)
	{
		*p++ = '\0';
	}
}
/*int	main(void)
{
	char	s[50] = "ooooooooo";
	int	n = 5;
	ft_bzero(s,n);
	printf("%s", s);
	return (0);
}*/
