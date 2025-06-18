/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 20:04:44 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 14:07:00 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	evalue_next_char(t_quotes *quot)
{
	if (quot->src[*quot->i + 1])
	{
		if (ft_is_space(quot->src[*quot->i + 1])
			|| is_operator_char(quot->src[*quot->i + 1]))
		{
			(*quot->m)++;
		}
	}
	else
		(*quot->m)++;
}

static void	parse_quotes_loop(t_quotes *quot, t_mini *mini)
{
	while (quot->src[*quot->i])
	{
		while (ft_is_space(quot->src[*quot->i]))
			(*quot->i)++;
		quot->result = &quot->result_base[*quot->m];
		if (quot->src[*quot->i] == '\'')
			single_quote(quot);
		else if (quot->src[*quot->i] == '\"')
			doble_quote(quot, mini);
		else
			no_quote(quot, mini);
		evalue_next_char(quot);
		(*quot->i)++;
	}
}

char	**fukking_quotes(char *src, t_mini *mini)
{
	t_quotes	quot;
	char		**result;
	size_t		j;
	int			i;
	int			m;

	i = 0;
	m = 0;
	j = 0;
	result = malloc((number_of_cmd_arg(src) + 1) * sizeof(char *));
	while (j <= number_of_cmd_arg(src))
		result[j++] = NULL;
	quot.src = src;
	quot.i = &i;
	quot.m = &m;
	quot.result_base = result;
	parse_quotes_loop(&quot, mini);
	if (middle_null(result, (number_of_cmd_arg(src))) == 1)
		result = remove_nulls(result, (number_of_cmd_arg(src)));
	return (result);
}
