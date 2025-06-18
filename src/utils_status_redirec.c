/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_status_redirec.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:57:36 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 17:01:09 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status_type	handle_simple_heredoc(t_list *list, char **mat_content, int *i)
{
	if (!mat_content[*i + 1])
		return (SYN_ERROR);
	if (safe_add_str(&list->redirecc, mat_content[*i]) != OK)
		return (MALLOC_ERROR);
	(*i)++;
	if (safe_add_str(&list->delim, mat_content[*i]) != OK)
		return (MALLOC_ERROR);
	return (OK);
}

t_status_type	handle_quoted_heredoc(t_list *list, char **mat_content, int *i)
{
	char	*redir_op;

	redir_op = take_the_redir(&mat_content[*i]);
	if (!redir_op)
		return (MALLOC_ERROR);
	if (safe_add_str(&list->redirecc, redir_op) != OK)
		return (free(redir_op), MALLOC_ERROR);
	free(redir_op);
	if (safe_add_str(&list->delim, mat_content[*i]) != OK)
		return (MALLOC_ERROR);
	return (OK);
}

t_status_type	handle_simple_redir(t_list *list, char **mat, int *i)
{
	t_status_type	status;

	if (!mat[*i + 1])
		return (SYN_ERROR);
	status = safe_add_str(&list->redirecc, mat[(*i)++]);
	if (status != OK)
		return (MALLOC_ERROR);
	if (ft_strncmp(mat[*i], "<", 1) == 0 || ft_strncmp(mat[*i], ">", 1) == 0)
		return (SYN_ERROR);
	if (safe_add_str(&list->fd, mat[*i]) != OK)
		return (MALLOC_ERROR);
	return (OK);
}

t_status_type	handle_complex_redir(t_list *list, char **mat, int *i)
{
	char			*redir_op;
	t_status_type	status;

	redir_op = take_the_redir(&mat[*i]);
	if (!redir_op)
		return (MALLOC_ERROR);
	status = safe_add_str(&list->redirecc, redir_op);
	free(redir_op);
	if (status != OK)
		return (MALLOC_ERROR);
	if (ft_strncmp(mat[*i], "<", 1) == 0 || ft_strncmp(mat[*i], ">", 1) == 0)
		return (SYN_ERROR);
	if (safe_add_str(&list->fd, mat[*i]) != OK)
		return (MALLOC_ERROR);
	return (OK);
}
