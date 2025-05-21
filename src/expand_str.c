/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:44:17 by ksudyn            #+#    #+#             */
/*   Updated: 2025/05/21 18:55:36 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

#include "pruebas.h"

// char *add_expand_str(char *src,char *matrix,int *i)
// {
// 	char *expanded;
// 	char *result = NULL;
// 	int j = *i;
// 	(void)matrix;
// 	while( src[j] && !ft_is_space(src[j]) && !is_quote(src[j]))
// 		j++;
// 	expanded = getenv(ft_substr(src,*i,j - *i));
// 	result = malloc((((ft_strlen(expanded) + ft_strlen(src)) + 1)) * sizeof(char));
// 	if(!result)
// 	{
// 		/* gestion de leaks*/
// 	}
// 	ft_strlcpy(result,matrix,ft_strlen(matrix) + 1);
// 	ft_strlcat(result,expanded,ft_strlen(matrix) + ft_strlen(expanded) + 1);
// 	*i = j - 1;
// 	return(result);
// }

char *extract_var_name(char *src, int *index)
{
    int j;
	char *var_name;

	j = *index;
    while (src[j] && !ft_is_space(src[j]) && !is_quote(src[j]) && src[j] != '$')
        j++;

    var_name = ft_substr(src, *index, j - *index);
    if (!var_name)
        return (NULL);

    *index = j - 1;
    return var_name;
}

char *concat_expanded(char *matrix, char *expanded)
{
    size_t len_matrix;
    size_t len_expanded;
	char *result;

	len_matrix = ft_strlen(matrix);
    len_expanded = ft_strlen(expanded);
    result = malloc(len_matrix + len_expanded + 1);
    if (!result)
        return (NULL);

    result[0] = '\0';
    ft_strlcpy(result, matrix, len_matrix + 1);
    ft_strlcat(result, expanded, len_matrix + len_expanded + 1);

    return result;
}

char *add_expand_str(char *src, char *matrix, int *i)
{
    char *var_name;
    char *expanded;
    char *result;

	*var_name = extract_var_name(src, i);
    if (!var_name)
        return (NULL);

    expanded = getenv(var_name);
    if (!expanded)
        expanded = "";

    result = concat_expanded(matrix, expanded);
    free(var_name);
    return result;
}
// Se pone result[0] = '\0'; antes de usar ft_strlcat,
// garantizando que la concatenación no acceda a memoria no inicializada.

// Se asegura liberar var_name después de su uso.
// La asignación de memoria para el resultado es más precisa (solo la suma necesaria)

// Antes se hacía getenv(ft_substr(...)) directamente,
// que genera una asignación dinámica que no se libera, provocando fugas.
// Ahora se guarda la variable temporal (var_name) y se libera al final.
