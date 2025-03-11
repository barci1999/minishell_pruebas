/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:53:46 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/02 11:52:14 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_2;
	int		len_1;
	int		len_3;
	char	*s3;

	s3 = NULL;
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	s3 = ft_calloc((len_1 + len_2 + 1), sizeof(char));
	if (s3 == NULL)
	{
		free(s3);
		return (NULL);
	}
	len_3 = len_1 + len_2 + 1;
	ft_strlcat(s3, s1, len_3);
	ft_strlcat(s3, s2, len_3);
	return (s3);
}
/*int main(void)
{
	const   char s1[] = "hola";
	const   char s2[]= "cocacola";
	printf("%s\n",ft_strjoin(s1, s2));
	//printf("%",ft_strlen(s1), ft_strlen(s2));
	return(0);
}*/