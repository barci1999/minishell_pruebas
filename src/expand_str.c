/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:44:17 by ksudyn            #+#    #+#             */
/*   Updated: 2025/06/17 20:36:55 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_var_name(char *src, int *index)
{
	int		j;
	char	*var_name;

	j = *index;
	while (src[j] && !ft_is_space(src[j]) && !is_quote(src[j]) && src[j] != '$')
		j++;
	var_name = ft_substr(src, *index, j - *index);
	if (!var_name)
		return (NULL);
	*index = j - 1;
	return (var_name);
}

char	*concat_expanded(char *matrix, char *expanded)
{
	size_t	len_matrix;
	size_t	len_expanded;
	char	*result;

	len_matrix = ft_strlen(matrix);
	len_expanded = ft_strlen(expanded);
	result = malloc(len_matrix + len_expanded + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	ft_strlcpy(result, matrix, len_matrix + 1);
	ft_strlcat(result, expanded, len_matrix + len_expanded + 1);
	return (result);
}

char	*get_env_value(t_mini *mini, char *var_name)
{
	t_list	*node;

	if(!var_name)
		return(NULL);
	node = mini->first_node;
	while (node)
	{
		if (ft_strcmp(node->variable, var_name) == 0)
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

char	*add_expand_str(t_mini *mini, char *src, char *matrix, int *i)
{
	char	*var_name;
	char	*expanded;
	char	*result;

	var_name = extract_var_name(src, i);
	if (!var_name)
		return (NULL);
	expanded = get_env_value(mini, var_name);
	if (!expanded)
		expanded = "";
	result = concat_expanded(matrix, expanded);
	free(var_name);
	return (result);
}

// Se pone result[0] = '\0'; antes de usar ft_strlcat,
// garantizando que la concatenación no acceda a memoria no inicializada.

// Se asegura liberar var_name después de su uso.
// La asignación de memoria para el resultado es más precisa
// (solo la suma necesaria)

// Antes se hacía getenv(ft_substr(...)) directamente,
// que genera una asignación dinámica que no se libera, provocando fugas.
// Ahora se guarda la variable temporal (var_name) y se libera al final.

// Falta revisar si usar la copia del env provoca fugas de memoria.