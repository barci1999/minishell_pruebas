#include "pruebas.h"

int	is_cmd(char *cmd)
{
	int		i;
	char	**path;
	char	*temp;

	i = 0;
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
	else if (token[0] == '$')
	{
		if (ft_strcmp(token, "$?") == 0)
			return (DOLLAR_EXIT);
		return (ENV_VAR);
	}
	else if (is_cmd(token))
		return (CMD);
	else
		return (INVALID);
}

void	tokenize(char *input)
{
	int				i;
	int				start;
	char			*token;
	int				flag_quote;
	char			quote_char;
	t_token_type	token_tipe;

	i = 0;
	start = 0;
	token = NULL;
	flag_quote = 0;
	quote_char = 0;
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
				token_tipe = classify_tokken(token);
				printf("%u\n", token_tipe);
				free(token);
			}
			start = i + 1;
		}
		i++;
	}
	if (i > start)
	{
		token = ft_substr(input, start, i - start);
		token_tipe = classify_tokken(token);
		printf("%u\n", token_tipe);
		free(token);
	}
}
int	main(int argc, char **argv, char **envp)
{
	char *input;
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
			tokenize(input);
	}
	return (0);
}