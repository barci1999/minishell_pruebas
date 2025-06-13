/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 20:03:58 by ksudyn            #+#    #+#             */
/*   Updated: 2025/06/13 20:06:33 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	analize_nbr(int *double_quote, int *single_quote)
{
	if (*double_quote % 2 == 0 && *single_quote % 2 == 0)
		return (true);
	else if (*double_quote == 0 && *single_quote % 2 == 0)
		return (true);
	else if (*double_quote % 2 == 0 && *single_quote == 0)
		return (true);
	else
		return (false);
}

static void	skip_double_quotes(char *src, int *i, int *double_quote)
{
	(*double_quote)++;
	(*i)++;
	while (src[*i] && src[*i] != '\"')
		(*i)++;
	if (src[*i] == '\"')
	{
		(*double_quote)++;
		(*i)++;
	}
}

static void	skip_single_quotes(char *src, int *i, int *single_quote)
{
	(*single_quote)++;
	(*i)++;
	while (src[*i] && src[*i] != '\'')
		(*i)++;
	if (src[*i] == '\'')
	{
		(*single_quote)++;
		(*i)++;
	}
}

bool	nbr_quotes_ok(char *src)
{
	int	i;
	int	double_quote;
	int	single_quote;

	i = 0;
	double_quote = 0;
	single_quote = 0;
	while (src[i])
	{
		if (src[i] == '\"')
			skip_double_quotes(src, &i, &double_quote);
		else if (src[i] == '\'')
			skip_single_quotes(src, &i, &single_quote);
		else
			i++;
	}
	return (analize_nbr(&double_quote, &single_quote));
}
