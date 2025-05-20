/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:09 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/20 17:27:43 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

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
