/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 19:34:23 by ksudyn            #+#    #+#             */
/*   Updated: 2025/06/17 19:30:33 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_quote(t_quotes *quot, t_mini *mini)
{
	char	*temp;

	temp = NULL;
	if (quot->src[*quot->i + 1] && quot->src[*quot->i] == '$')
	{
		(*quot->i)++;
		temp = take_the_expand(quot->src, quot->i, mini);
		*quot->result = ft_free_strjoin(*quot->result, temp);
		return ;
	}
	if (is_operator_char(quot->src[*quot->i]))
	{
		*quot->result = add_chr_to_str(NULL, quot->src[*quot->i]);
		if (quot->src[*quot->i + 1]
			&& is_operator_char(quot->src[*quot->i + 1]))
		{
			(*quot->i)++;
			*quot->result = add_chr_to_str(*quot->result, quot->src[*quot->i]);
			
		}
		if (!ft_is_space(quot->src[*quot->i + 1]))
		{
			if(is_operator_char(quot->src[*quot->i + 1]))
				return;
			(*quot->m)++;
		}
		return ;
	}
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
