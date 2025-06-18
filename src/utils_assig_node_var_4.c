/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_assig_node_var_4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 20:40:57 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 20:43:30 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_varnodes(t_varnodes *v)
{
	v->i = 0;
	v->start = false;
}

int	process_cmd(char **c, t_list *l, t_varnodes *v, t_general *g)
{
	if (mod_cmd_and_args(l, c, v, g) != OK)
		return (print_error(c[v->i], "command not found", 127), 1);
	v->start = true;
	return (0);
}

int	process_word(char **c, t_list *l, t_varnodes *v)
{
	l->cmd_arg = add_str_to_mat(l->cmd_arg, c[v->i]);
	if (!l->cmd_arg)
		return (print_error("malloc", "memory allocation failed", 1), 1);
	v->i++;
	return (0);
}

int	process_redir(char **c, t_list *l, t_varnodes *v, t_general *g)
{
	if (mod_redir_and_fd(l, c, v, g) != OK)
		return (print_error(c[v->i], "redirection error", 2), 1);
	return (0);
}

int	process_node_cases(char **c, t_list *l, t_varnodes *v, t_general *g)
{
	if (!v->start && (v->type == CMD || v->type == WORD))
	{
		if (process_cmd(c, l, v, g))
			return (1);
	}
	else if (v->start && v->type == WORD)
	{
		if (process_word(c, l, v))
			return (1);
	}
	else if (v->type == REDIREC)
	{
		if (process_redir(c, l, v, g))
			return (1);
	}
	else
	{
		if (*c[v->i] == '\0')
			return (0);
		print_error(c[v->i], "syntax error", 2);
		return (1);
	}
	return (0);
}
