/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:27:19 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/01 18:27:57 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*dest;
	int		i;

	i = 0;
	if ((s == NULL) || f == (NULL))
		return (NULL);
	dest = malloc((ft_strlen(s) + 1) * (sizeof(char)));
	if (dest == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*char to_upper_if_odd(unsigned int index, char c)
{
	if (index % 2 == 1)
	{
		return (ft_toupper(c));
	}
	return (c);
}
int	main(void)
{
	char	*s = "cocacola";
	printf("%s",ft_strmapi(s,to_upper_if_odd));
	return (0);
}*/