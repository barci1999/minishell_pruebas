/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_redirecc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 18:22:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 19:34:13 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status_type	handle_heredoc(t_list *list, char **mat_content, t_varnodes *var_nodes,
		t_general *data_gen)
{
	char			*itoa_result;
	char			*temp;
	t_status_type	status;

	if (ft_strcmp(mat_content[var_nodes->i], "<<") == 0)
		status = handle_simple_heredoc(list, mat_content, var_nodes);
	else
		status = handle_quoted_heredoc(list, mat_content, var_nodes);
	if (status != OK)
		return (status);
	itoa_result = ft_itoa(data_gen->tem_heredoc++);
	if (!itoa_result)
		return (MALLOC_ERROR);
	temp = ft_strjoin("temp_here_", itoa_result);
	if (!temp)
		return (free(itoa_result), MALLOC_ERROR);
	if (safe_add_str(&list->fd, temp) != OK)
		return (free(itoa_result), MALLOC_ERROR);
	free(temp);
	free(itoa_result);
	(var_nodes->i)++;
	return (OK);
}

t_status_type	handle_fd_redir(t_list *list, char **mat_content, t_varnodes *var_nodes)
{
	t_status_type	status;

	if (ft_strcmp(mat_content[var_nodes->i], "<") == 0 || ft_strcmp(mat_content[var_nodes->i],
			">") == 0 || ft_strcmp(mat_content[var_nodes->i], ">>") == 0)
		status = handle_simple_redir(list, mat_content, var_nodes);
	else
		status = handle_complex_redir(list, mat_content, var_nodes);
	if (status != OK)
		return (status);
	(var_nodes->i)++;
	return (OK);
}

t_status_type	mod_redir_and_fd(t_list *list, char **mat_content,t_varnodes *var_nodes,
		t_general *data_gen)
{
	if (!mat_content[var_nodes->i] || up_stat(mat_content, var_nodes, data_gen) != REDIREC)
		return (SYN_ERROR);
	if (ft_strncmp(mat_content[var_nodes->i], "<<", 2) == 0)
		return (handle_heredoc(list, mat_content, var_nodes, data_gen));
	else if (ft_strncmp(mat_content[var_nodes->i], "<", 1) == 0
		|| ft_strncmp(mat_content[var_nodes->i], ">", 1) == 0
		|| ft_strncmp(mat_content[var_nodes->i], ">>", 1) == 0)
		return (handle_fd_redir(list, mat_content, var_nodes));
	return (OK);
}
