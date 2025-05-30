/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_redirecc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:22:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/30 19:33:39 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"

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

t_status_type	handle_heredoc(t_list *list, char **mat_content, int *i,
		t_general *data_gen)
{
	char			*itoa_result;
	char *temp;
	t_status_type	status;

	if (ft_strcmp(mat_content[*i], "<<") == 0)
		status = handle_simple_heredoc(list, mat_content, i);
	else
		status = handle_quoted_heredoc(list, mat_content, i);
	if (status != OK)
		return (status);
	itoa_result = ft_itoa(data_gen->tem_heredoc++);
	if (!itoa_result)
		return (MALLOC_ERROR);
	temp = ft_strjoin("temp_here_",itoa_result);
	if(!temp)
		return (free(itoa_result),MALLOC_ERROR);
	if (safe_add_str(&list->fd, temp) != OK)
		return (free(itoa_result), MALLOC_ERROR);
	free(temp);
	free(itoa_result);
	(*i)++;
	return (OK);
}

t_status_type	handle_fd_redir(t_list *list, char **mat_content, int *i)
{
	char	*redir_op;

	if (ft_strcmp(mat_content[*i], "<") == 0 || ft_strcmp(mat_content[*i],
			">") == 0 || ft_strcmp(mat_content[*i], ">>") == 0)
	{
		if (!mat_content[*i + 1])
			return (SYN_ERROR);
		if (safe_add_str(&list->redirecc, mat_content[(*i)++]) != OK)
			return (MALLOC_ERROR);
		if (safe_add_str(&list->fd, mat_content[*i]) != OK)
			return (MALLOC_ERROR);
	}
	else
	{
		redir_op = take_the_redir(&mat_content[*i]);
		if (!redir_op)
			return (MALLOC_ERROR);
		if (safe_add_str(&list->redirecc, redir_op) != OK)
			return (free(redir_op), MALLOC_ERROR);
		free(redir_op);
		if (safe_add_str(&list->fd, mat_content[*i]) != OK)
			return (MALLOC_ERROR);
	}
	(*i)++;
	return (OK);
}

t_status_type	mod_redir_and_fd(t_list *list, char **mat_content, int *i,
		t_general *data_gen)
{
	if (!mat_content[*i] || update_status(mat_content, i, data_gen) != REDIREC)
		return (SYN_ERROR);
	if (ft_strncmp(mat_content[*i], "<<", 2) == 0)
		return (handle_heredoc(list, mat_content, i, data_gen));
	else if (ft_strncmp(mat_content[*i], "<", 1) == 0
		|| ft_strncmp(mat_content[*i], ">", 1) == 0
		|| ft_strncmp(mat_content[*i], ">>", 1) == 0)
		return (handle_fd_redir(list, mat_content, i));
	return (OK);
}
