#include "pruebas.h"

int	is_cmd(char *cmd)
{
	int		i;
	char	**path;
	char	*temp;

	i = 0;
	if(access(cmd,X_OK) == 0)
		return(1);
	path = ft_split(getenv("PATH"), ':');
	temp = NULL;
	while (path[i] != NULL)
	{
		temp = ft_get_strjoin(path[i], "/");
		path[i] = ft_get_strjoin(temp, cmd);
		if (access(path[i], X_OK) == 0)
			return (ft_free_matrix(path),1);
		i++;
	}
	return (ft_free_matrix(path),0);
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
	else if (ft_strcmp(token,"\"") == 0 || ft_strcmp(token,"\'")  == 0)
		return(QUOTE);
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

void	tonkenize(char *input)
{
	char			**tokens;
	int				i;
	t_token_type	token_type;

	tokens = ft_split(input, ' ');
	i = 0;
	while (tokens[i])
	{
		token_type = classify_tokken(tokens[i]);
		if (token_type == CMD)
			printf("CMD: %s\n", tokens[i]);
		else if (token_type == ARG)
			printf("ARG: %s\n", tokens[i]);
		else if (token_type == PIPE)
			printf("PIPE: %s\n", tokens[i]);
		else if (token_type == REDIR_IN)
			printf("REDIR_IN: %s\n", tokens[i]);
		else if (token_type == REDIR_OUT)
			printf("REDIR_OUT: %s\n", tokens[i]);
		else if (token_type == REDIR_APPEND)
			printf("REDIR_APPEND: %s\n", tokens[i]);
		else if (token_type == HEREDOC)
			printf("HEREDOC: %s\n", tokens[i]);
		else if (token_type == ENV_VAR)
			printf("ENV_VAR: %s\n", tokens[i]);
		else if (token_type == DOLLAR_EXIT)
			printf("DOLLAR_EXIT: %s\n", tokens[i]);
		else if (token_type == QUOTE)
			printf("QUOTE: %s\n", tokens[i]);
		else if (token_type == INVALID)
			printf("INVALID: %s\n", tokens[i]);
		i++;
	}
	ft_free_matrix(tokens);
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
			tonkenize(input);
	}
	return (0);
}