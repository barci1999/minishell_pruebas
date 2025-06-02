/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 16:40:27 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/02 21:58:43 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	const char	*temp;
	char		*ret;
	size_t		n;

	n = ft_strlen(s1);
	temp = s1 + n - 1;
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	while (*s1 && ft_strchr(set, *temp))
		temp--;
	ret = ft_substr(s1, 0, temp - s1 + 1);
	return (ret);
}
/*int	main(void)
{
	const char *s1 = "hola";
	const char *set = "";
	printf("%s", ft_strtrim(s1, set));
	return (0);
}*/