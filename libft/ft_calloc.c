/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:46:49 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:48:56 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*array;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	array = (char *) malloc(count * size);
	if (array == NULL)
		return (NULL);
	ft_memset(array, 0, (count * size));
	return (array);
}

/*int	main(void)
{
   char *replica;
   char *original;
   size_t nmemb;

   nmemb = 10;
   replica = ft_calloc(, );
   original = calloc( , );
   printf("%p\n", replica);
   printf("%p\n", original);

   return(0);
}*/