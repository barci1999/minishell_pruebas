/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:14:32 by pablalva          #+#    #+#             */
/*   Updated: 2024/10/03 15:56:33 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	positive_numbers(int n, int i, char *dest)
{
	while (n > 0)
	{
		dest[i] = ((n % 10) + '0');
		n = n / 10;
		(i)--;
	}
	return (n);
}

static int	negative_numbers(int n, int *len)
{
	if (n < 0)
	{
		(*len)++;
		n = -n;
	}
	return (n);
}

static char	*max(int n)
{
	if (n == 2147483647)
		return (ft_strdup("2147483647"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (NULL);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*dest;
	int		temp;
	int		is_negative;

	len = 0;
	if (n == 0)
		return (ft_strdup("0"));
	if ((n >= 2147483647) || (n <= -2147483648))
		return (max(n));
	is_negative = (n < 0);
	n = negative_numbers(n, &len);
	temp = n;
	while (temp > 0)
	{
		temp = temp / 10;
		len++;
	}
	dest = ft_calloc((len + 1), (sizeof(char)));
	if (!dest)
		return (NULL);
	positive_numbers(n, (len - 1), dest);
	if (is_negative)
		dest[0] = '-';
	return (dest);
}
