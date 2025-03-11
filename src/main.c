#include"pruebas.h"

int is_cmd(char *cmd)
{
	int i = 0;
	char **path = ft_split(getenv("PATH"),':');
	char *temp = NULL;
	while (path[i] != NULL)
	{

		temp = ft_strjoin(path[i],"/");
			free(path[i]);
		path[i] = ft_strjoin(temp,cmd);
		if(access(path[i],X_OK) == 0)
		{
			free(path[i]);
			free(temp);
			return(1);
		}
		else
		{
			free(path[i]);
			i++;
		}
	}
	free(path);
	return(0);
}
void parse_split(char **matrix)
{
	int i = 0;
	t_list *list;
	list = NULL;

	while (matrix[i] != NULL)
	{
		if(is_cmd(matrix[i]))
		{
			printf("%s es un comando\n",matrix[i]);	
		}
		i++;
	}
}
int main(int argc,char **argv,char **envp)
{
	char *input;
	(void)argv;
	(void)envp;
	if(argc < 1)
		return(1);
	while(1)
	{
		input = readline("minishell> ");
		if(input == NULL)
			break;
		if(*input != '\0')
			parse_split(ft_split(input,' '));
	}
	return(0);
}