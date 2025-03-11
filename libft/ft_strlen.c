/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:09 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:51:18 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		return (0);
	}
	while (s[i] != '\0')
		i++;
	return (i);
}
/*int	main(void)
{
	const	char s[] = "cocacola";
	printf("%d",ft_strlen(NULL));
	//printf("%d",strlen(NULL));
	return(0);
}*/
