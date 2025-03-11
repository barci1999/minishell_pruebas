/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 12:13:07 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:51:39 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	b;
	size_t	l;

	b = 0;
	l = 0;
	if (*little == '\0')
		return ((char *)big);
	while (b < len && big[b] != '\0')
	{
		l = 0;
		while (b + l < len && big[b + l] == little[l])
		{
			if (little[l] == '\0')
				return ((char *)&big[b]);
			l++;
		}
		if (little[l] == '\0')
			return ((char *)&big[b]);
		b++;
	}
	return (NULL);
}
/*int	main(void)
{
  const char big[] = "my favorite animal is";
  const char little[] = " ";
  size_t len = 8;

  printf("%s\n", ft_strnstr(big,little,len));
  return (0);
}*/