/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:25:26 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/07 20:14:35 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pruebas.h"
int is_builting(char *token)
{
	if (ft_strcmp(token, "echo") == 0)
		return(1);
	else if (ft_strcmp(token, "cd") == 0)
		return(1);
	else if (ft_strcmp(token, "pwd") == 0)
		return(1);
	else if (ft_strcmp(token, "export") == 0)
		return(1);
	else if (ft_strcmp(token, "unset") == 0)
		return(1);
	else if (ft_strcmp(token, "env") == 0)
		return(1);
	else if (ft_strcmp(token, "exit") == 0)
		return(1);
	return(0);	
}

int	is_cmd(char *cmd)
{
	int		i;
	char	**path;
	char	*temp;
	i = 0;
	
	if (strncmp(cmd, "VAR_", 4) == 0)
        return (0);
	if (access(cmd, X_OK) == 0)
		return (1);
	path = ft_split(getenv("PATH"), ':');
	temp = NULL;
	while (path[i] != NULL)
	{
		temp = ft_get_strjoin(path[i], "/");
		path[i] = ft_get_strjoin(temp, cmd);
		if (access(path[i], X_OK) == 0)
			return (ft_free_matrix(path), 1);
		i++;
	}
	return (ft_free_matrix(path), 0);
}

t_token_type	classify_tokken(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	else if (ft_strcmp(token, "<") == 0)
		return (REDIR_IN);
	else if (ft_strcmp(token, ">") == 0)
		return (REDIR_OUT);
	else if (ft_strcmp(token, ">>") == 0)
		return (REDIR_APPEND);
	else if (ft_strcmp(token, "<<") == 0)
		return (HEREDOC);
	else if (ft_strcmp(token, "\"") == 0 || ft_strcmp(token, "\'") == 0)
		return (QUOTE);
	else if (ft_strcmp(token, "$?") == 0)
			return (DOLLAR_EXIT);
	else if (is_builting(token))
		return(BUILTIN);
	else if (is_cmd(token))
		return (CMD);
	else
		return (WORD);
}

t_list	*tokenize(char *input)
{
	int				i;
	int				start;
	char			*token;
	int				flag_quote;
	char			quote_char;
	t_token_type	token_tipe;
	t_list			*tokens;

	i = 0;
	start = 0;
	token = NULL;
	flag_quote = 0;
	quote_char = 0;
	tokens = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == '\'' || input[i] == '\"')
		{
			if (flag_quote && input[i] == quote_char)
				flag_quote = 0;
			else if (!flag_quote)
			{
				flag_quote = 1;
				quote_char = input[i];
			}
		}
		else if (input[i] == ' ' && !flag_quote)
		{
			if (i > start)
			{
				token = ft_substr(input, start, i - start);
				if(token == NULL)
				{
					free_list(&tokens);
					free(token);
					exit(1);
				}
				token_tipe = classify_tokken(token);
				if (node_to_end(&tokens, new_doble_node(token_tipe, token)) == -1)
				{
					free_list(&tokens);
					exit(1);
				}
				free(token);
			}
			start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		token = ft_substr(input, start, i - start);
		if(token == NULL)
		{
			free_list(&tokens);
			free(token);
			exit(1);
		}
		token_tipe = classify_tokken(token);
		if (node_to_end(&tokens, new_doble_node(token_tipe, token)) == -1)
		{
			free_list(&tokens);
			exit(1);
		}
		free(token);
	}
	change_word(&tokens);
	//sintax_list(&tokens);
	return (tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input = NULL;
	char *temp = NULL;

	(void)argv;
	(void)envp;
	if (argc < 1)
		return (1);
	while (1)
	{
		input = readline("minishell> ");
		if (input == NULL)
			break ;
		if (*input != '\0')
			{
				add_history(input);
				temp = ft_strdup(expand_str(input));
				input = ft_strdup(temp);
				print_list(tokenize(input));
			}
			
	}
	return (0);
}
