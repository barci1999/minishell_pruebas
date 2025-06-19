/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:13:06 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/19 17:18:52 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_expansion(t_quotes *q, t_mini *mini)
{
	char	*temp;

	if (q->src[*q->i + 1] && q->src[*q->i] == '$')
	{
		(*q->i)++;
		temp = take_the_expand(q->src, q->i, mini);
		if (q->src[*q->i] == '\0' || ft_is_space(q->src[*q->i]))
			(*q->i)--;
		*q->result = ft_free_strjoin(*q->result, temp);
		if (q->src[*q->i] == '$')
			(*q->i)--;
		return (1);
	}
	return (0);
}

static int	handle_operator(t_quotes *q)
{
	if (is_operator_char(q->src[*q->i]))
	{
		*q->result = add_chr_to_str(NULL, q->src[*q->i]);
		if (q->src[*q->i + 1] && is_operator_char(q->src[*q->i + 1]))
		{
			(*q->i)++;
			*q->result = add_chr_to_str(*q->result, q->src[*q->i]);
		}
		if (!ft_is_space(q->src[*q->i + 1]))
		{
			if (!is_operator_char(q->src[*q->i + 1]))
				(*q->m)++;
		}
		return (1);
	}
	return (0);
}

void	no_quote(t_quotes *quot, t_mini *mini)
{
	int	handled;

	handled = handle_expansion(quot, mini);
	if (handled)
		return ;
	handled = handle_operator(quot);
	if (handled)
		return ;
	*quot->result = add_chr_to_str(*quot->result, quot->src[*quot->i]);
}

void	single_quote(t_quotes *quot)
{
	if (!quot->src[*quot->i + 1])
		return ;
	else
		(*quot->i)++;
	while (quot->src[*quot->i] != '\'')
	{
		*quot->result = add_chr_to_str(*quot->result, quot->src[*quot->i]);
		(*quot->i)++;
	}
}

void	doble_quote(t_quotes *quo, t_mini *mini)
{
	char	*temp;

	if (!quo->src[*quo->i + 1])
		return ;
	else
		(*quo->i)++;
	while (quo->src[*quo->i] != '\"')
	{
		if (quo->src[*quo->i + 1] && quo->src[*quo->i] == '$'
			&& (ft_isalnum(quo->src[*quo->i + 1])
				|| quo->src[*quo->i + 1] == '_'
				|| quo->src[*quo->i + 1] == '?'))
		{
			(*quo->i)++;
			temp = take_the_expand(quo->src, quo->i, mini);
			*quo->result = ft_free_strjoin(*quo->result, temp);
			if (quo->src[*quo->i] == '\"')
				break ;
		}
		else
		{
			*quo->result = add_chr_to_str(*quo->result, quo->src[*quo->i]);
			(*quo->i)++;
		}
	}
}
