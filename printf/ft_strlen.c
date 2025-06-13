/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:09 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/02 21:17:48 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (*s == '\0')
		return (0);
	while (s[i])
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
