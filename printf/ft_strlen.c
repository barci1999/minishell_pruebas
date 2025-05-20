/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:57:09 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/20 18:51:46 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
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

