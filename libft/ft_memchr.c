/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:15:15 by pablalva          #+#    #+#             */
/*   Updated: 2024/09/30 17:45:48 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;
	unsigned char	l;

	i = 0;
	temp = (unsigned char *)s;
	l = (unsigned char)c;
	while (i != n)
	{
		if (temp[i] == l)
			return ((void *)&temp[i]);
		i++;
	}
	return (NULL);
}
/*int main(void)
{
  char s [] = "cocacola";
  int c = 'c';
  size_t n = 9;
  printf("%s",ft_memchr(s,c,NULL));
  printf("%s",memchr(s,c,NULL));
  return(0);
}*/
