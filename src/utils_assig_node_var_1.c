/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_assig_node_var_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:59:38 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 21:03:38 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_quotes(const char *src, int *i, size_t *count)
{
	char	quote;

	quote = src[(*i)++];
	while (src[*i] && src[*i] != quote)
		(*i)++;
	if (src[*i] == quote)
		(*i)++;
	(*count)++;
}

static void	skip_operator(const char *src, int *i, size_t *count)
{
	if ((src[*i] == '>' && src[*i + 1] == '>')
		|| (src[*i] == '<' && src[*i + 1] == '<'))
		*i += 2;
	else
		(*i)++;
	(*count)++;
}

static void	skip_word(const char *src, int *i, size_t *count)
{
	while (src[*i] && !ft_is_space(src[*i]) && !is_quote(src[*i])
		&& !is_operator_char(src[*i]))
		(*i)++;
	(*count)++;
}

size_t	number_of_cmd_arg(const char *src)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (src[i])
	{
		while (src[i] && ft_is_space(src[i]))
			i++;
		if (!src[i])
			break ;
		if (is_quote(src[i]))
			skip_quotes(src, &i, &count);
		else if (is_operator_char(src[i]))
			skip_operator(src, &i, &count);
		else
			skip_word(src, &i, &count);
	}
	return (count);
}

t_list	*asigg_cont_list(t_list *list, t_general *data_gen, t_mini *mini)
{
	t_list	*current;
	char	**mat_content;

	mat_content = NULL;
	current = list;
	data_gen->tem_heredoc = 0;
	data_gen->my_env = env_list_to_array(mini);
	while (current)
	{
		mat_content = fukking_quotes(current->content, mini);
		if (!mat_content)
			return (ft_free_mat(mat_content), NULL);
		if (assig_var_node(mat_content, current, data_gen) != 0)
		{
			ft_free_mat(mat_content);
			free_list(&list);
			return (NULL);
		}
		ft_free_mat(mat_content);
		current = current->next;
	}
	return (list);
}
