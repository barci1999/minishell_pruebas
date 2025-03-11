/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:48:46 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:51:25 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (c1[i] != c2[i])
			return (c1[i] - c2[i]);
		if (c1[i] == '\0' || c2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
/*int main(void)
{
  const char *s1 = "the cake is a lie !\0I'm hidden lol\r\n";
  const char *s2 ="there is no stars in the sky";
  size_t n = strlen("the cake is a lie !\0I'm hidden lol\r\n");
  printf("%i",ft_strncmp(s1,s2,n));
  printf("%i",strncmp(s1,s2,n));
  return(0);
}*/
