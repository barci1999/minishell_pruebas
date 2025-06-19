/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 22:36:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/19 19:39:59 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_mini *mini)
{
	if (!mini)
		return ;
	free_list(&mini->first_node);
}

int	comprove_first_char(char *src)
{
	int	i;

	i = 0;
	while (src[i] && ft_is_space(src[i]))
		i++;
	if (src[i] == '\0' || src[i] == '|')
		return (1);
	else
		return (0);
}

int	comprove_last_char(char *src)
{
	int		i;
	char	c;

	i = 0;
	while (src[i])
	{
		c = src[i];
		i++;
	}
	if (c == '|')
		return (1);
	else
		return (0);
}

int	comprove_doble_pipe(char *src)
{
	int		i;
	char	quote;

	i = -1;
	while (src[++i])
	{
		if (src[i] == '\'' || src[i] == '\"')
		{
			quote = src[i];
			while (src[++i] && src[i] != quote)
				;
		}
		else if (src[i] == '|')
		{
			while (src[++i] && (src[i] == ' ' || src[i] == '\t'))
				;
			if (src[i] == '|')
				return (1);
		}
	}
	return (0);
}

int	comprove_input(char *input)
{
	if (!input)
		return (1);
	if (nbr_quotes_ok(input) == false)
		return (1);
	if (comprove_first_char(input) == 1)
		return (1);
	if (comprove_last_char(input) == 1)
		return (1);
	if (comprove_doble_pipe(input) == 1)
		return (1);
	return (0);
}
