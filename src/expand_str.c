/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:44:17 by ksudyn            #+#    #+#             */
/*   Updated: 2025/05/20 18:16:53 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

char *add_expand_str(char *src,char *matrix,int *i)
{
	char *expanded;
	char *result = NULL;
	int j = *i;
	(void)matrix;
	while( src[j] && !ft_is_space(src[j]) && !is_quote(src[j]))
		j++;
	expanded = getenv(ft_substr(src,*i,j - *i));
	result = malloc((((ft_strlen(expanded) + ft_strlen(src)) + 1)) * sizeof(char));
	if(!result)
	{
		/* gestion de leaks*/
	}
	ft_strlcpy(result,matrix,ft_strlen(matrix) + 1);
	ft_strlcat(result,expanded,ft_strlen(matrix) + ft_strlen(expanded) + 1);
	*i = j - 1;
	return(result);
}
