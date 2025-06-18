
#include "minishell.h"

#define WIDTH 48
#define WIDTH_2 48
#define WIDTH_3 48

// Función auxiliar para limpiar strings (quita \n, \t, etc.)
void sanitize_string(const char *src, char *dest, int max_len)
{
    int i = 0;
    while (*src && i < max_len - 1)
    {
        if (*src == '\n' || *src == '\t' || *src < 32)
            dest[i++] = ' ';
        else
            dest[i++] = *src;
        src++;
    }
    dest[i] = '\0';
}

// Imprime una línea del cuadro, asegurando longitud exacta
void print_box_line(const char *prefix, const char *value)
{
    char clean_value[256];
    char full[WIDTH + 1];
    char buffer[WIDTH + 1];

    sanitize_string(value ? value : "(null)", clean_value, sizeof(clean_value));
    snprintf(full, sizeof(full), "%s: %s", prefix, clean_value);

    if ((int)strlen(full) > WIDTH)
        snprintf(buffer, sizeof(buffer), "%.*s", WIDTH, full);
    else
        snprintf(buffer, sizeof(buffer), "%-*s", WIDTH, full);

    printf("║%s║\n", buffer);
}

// Función para imprimir la lista de comandos
void print_cmd_list(t_list *list)
{
    int i = 0;
    int j, r, f, d;

    while (list)
    {
        printf("╔════════════════════════════════════════════════╗\n");

        char title[WIDTH + 1];
        snprintf(title, sizeof(title), "Nodo %d", i);
        printf("║%-*s║\n", WIDTH, title);

        printf("╠════════════════════════════════════════════════╣\n");

        print_box_line("content", list->content);
        print_box_line("cmd_path", list->cmd_path);
        print_box_line("cmd_name", list->cmd_name);

        printf("╠════════════════════════════════════════════════╣\n");
        print_box_line("cmd_arg", "");

        if (list->cmd_arg)
        {
            j = 0;
            while (list->cmd_arg[j])
            {
                char clean_arg[256];
                char arg_line[WIDTH + 1];
                char output[WIDTH + 1];

                sanitize_string(list->cmd_arg[j], clean_arg, sizeof(clean_arg));
                snprintf(arg_line, sizeof(arg_line), "   [%d] -> %s", j, clean_arg);

                if ((int)strlen(arg_line) > WIDTH)
                    snprintf(output, sizeof(output), "%.*s", WIDTH, arg_line);
                else
                    snprintf(output, sizeof(output), "%-*s", WIDTH, arg_line);

                printf("║%s║\n", output);
                j++;
            }
            char final_line[WIDTH + 1];
            snprintf(final_line, sizeof(final_line), "   [%d] -> (null)", j);
            printf("║%-*s║\n", WIDTH, final_line);
        }

        printf("╠════════════════════════════════════════════════╣\n");
        print_box_line("redirects", "");

        if (list->redirecc)
        {
            r = 0;
            while (list->redirecc[r])
            {
                char clean_red[256];
                char red_line[WIDTH_2 + 1];
                char output_red[WIDTH_2 + 1];

                sanitize_string(list->redirecc[r], clean_red, sizeof(clean_red));
                snprintf(red_line, sizeof(red_line), "   [%d] -> %s", r, clean_red);

                if ((int)strlen(red_line) > WIDTH_2)
                    snprintf(output_red, sizeof(output_red), "%.*s", WIDTH_2, red_line);
                else
                    snprintf(output_red, sizeof(output_red), "%-*s", WIDTH_2, red_line);

                printf("║%s║\n", output_red);
                r++;
            }
            char final_red[WIDTH_2 + 1];
            snprintf(final_red, sizeof(final_red), "   [%d] -> (null)", r);
            printf("║%-*s║\n", WIDTH_2, final_red);
        }
        else
        {
            printf("║%-*s║\n", WIDTH_2, "   (null)");
        }

        printf("╠════════════════════════════════════════════════╣\n");
        print_box_line("fd", "");

        if (list->fd)
        {
            f = 0;
            while (list->fd[f])
            {
                char clean_fd[256];
                char fd_line[WIDTH_3 + 1];
                char output_fd[WIDTH_3 + 1];

                sanitize_string(list->fd[f], clean_fd, sizeof(clean_fd));
                snprintf(fd_line, sizeof(fd_line), "   [%d] -> %s", f, clean_fd);

                if ((int)strlen(fd_line) > WIDTH_3)
                    snprintf(output_fd, sizeof(output_fd), "%.*s", WIDTH_3, fd_line);
                else
                    snprintf(output_fd, sizeof(output_fd), "%-*s", WIDTH_3, fd_line);

                printf("║%s║\n", output_fd);
                f++;
            }
            char final_fd[WIDTH_3 + 1];
            snprintf(final_fd, sizeof(final_fd), "   [%d] -> (null)", f);
            printf("║%-*s║\n", WIDTH, final_fd);
        }
        else
        {
            printf("║%-*s║\n", WIDTH_3, "   (null)");
        }

        printf("╠════════════════════════════════════════════════╣\n");
        print_box_line("delim", "");

        if (list->delim)
        {
            d = 0;
            while (list->delim[d])
            {
                char clean_delim[256];
                char delim_line[WIDTH + 1];
                char output_delim[WIDTH + 1];

                sanitize_string(list->delim[d], clean_delim, sizeof(clean_delim));
                snprintf(delim_line, sizeof(delim_line), "   [%d] -> %s", d, clean_delim);

                if ((int)strlen(delim_line) > WIDTH)
                    snprintf(output_delim, sizeof(output_delim), "%.*s", WIDTH, delim_line);
                else
                    snprintf(output_delim, sizeof(output_delim), "%-*s", WIDTH, delim_line);

                printf("║%s║\n", output_delim);
                d++;
            }
            char final_delim[WIDTH + 1];
            snprintf(final_delim, sizeof(final_delim), "   [%d] -> (null)", d);
            printf("║%-*s║\n", WIDTH, final_delim);
        }
        else
        {
            printf("║%-*s║\n", WIDTH, "   (null)");
        }

        printf("╚════════════════════════════════════════════════╝\n\n");

        list = list->next;
        i++;
    }
}



// void	no_quote(t_quotes *quot, t_mini *mini)
// {
// 	char	*temp;

// 	temp = NULL;
// 	if (quot->src[*quot->i + 1] && quot->src[*quot->i] == '$')
// 	{
// 		(*quot->i)++;
// 		temp = take_the_expand(quot->src, quot->i, mini);
// 		if (quot->src[*quot->i] == '\0')
// 			(*quot->i)--;
// 		*quot->result = ft_free_strjoin(*quot->result, temp);
// 		return ;
// 	}
// 	if (is_operator_char(quot->src[*quot->i]))
// 	{
// 		*quot->result = add_chr_to_str(NULL, quot->src[*quot->i]);
// 		if (quot->src[*quot->i + 1]
// 			&& is_operator_char(quot->src[*quot->i + 1]))
// 		{
// 			(*quot->i)++;
// 			*quot->result = add_chr_to_str(*quot->result, quot->src[*quot->i]);
// 		}
// 		if (!ft_is_space(quot->src[*quot->i + 1]))
// 		{
// 			if (is_operator_char(quot->src[*quot->i + 1]))
// 				return ;
// 			(*quot->m)++;
// 		}
// 		return ;
// 	}
// 	*quot->result = add_chr_to_str(*quot->result, quot->src[*quot->i]);
// }




// int	assig_var_node(char **content, t_list *list, t_general *data_gen)
// {
// 	t_varnodes var_nodes;

// 	var_nodes.start = false;
// 	var_nodes.i = 0;
// 	while (content[var_nodes.i])
// 	{
// 		var_nodes.type = up_stat(content,&var_nodes, data_gen);
// 		if (!var_nodes.start && (var_nodes.type == CMD || var_nodes.type == WORD))
// 		{
// 			if (mod_cmd_and_args(list, content,&var_nodes, data_gen) != OK)
// 				return (print_error(content[var_nodes.i], "command not found", 127),1);
// 			var_nodes.start = true;
// 		}
// 		else if (var_nodes.start && up_stat(content,&var_nodes, data_gen) == WORD)
// 		{
// 			list->cmd_arg = add_str_to_mat(list->cmd_arg, content[var_nodes.i]);
// 			if (!list->cmd_arg)
// 				return (print_error("malloc", "memory allocation failed", 1),1);
// 			var_nodes.i++;
// 		}
// 		else if (up_stat(content, &var_nodes, data_gen) == REDIREC)
// 		{
// 			if (mod_redir_and_fd(list, content, &var_nodes, data_gen) != OK)
// 				return (print_error(content[var_nodes.i], "redirection error", 2),1);
// 		}
// 		else
// 		{
// 			if (*content[var_nodes.i] == '\0')
// 				return (0);
// 			print_error(content[var_nodes.i], "syntax error", 2);
// 			return (1);
// 		}
// 	}
// 	return (0);
// }

// size_t	number_of_cmd_arg(const char *src)
// {
// 	int		i;
// 	size_t	count;
// 	char	quote;

// 	i = 0;
// 	count = 0;
// 	while (src[i])
// 	{
// 		while (src[i] && ft_is_space(src[i]))
// 			i++;
// 		if (!src[i])
// 			break ;
// 		if (is_quote(src[i]))
// 		{
// 			quote = src[i++];
// 			while (src[i] && src[i] != quote)
// 				i++;
// 			if (src[i] == quote)
// 				i++;
// 			count++;
// 		}
// 		else if (is_operator_char(src[i]))
// 		{
// 			if ((src[i] == '>' && src[i + 1] == '>') || (src[i] == '<' && src[i
// 					+ 1] == '<'))
// 				i += 2;
// 			else
// 				i += 1;
// 			count++;
// 		}
// 		else
// 		{
// 			while (src[i] && !ft_is_space(src[i]) && !is_quote(src[i])
// 				&& !is_operator_char(src[i]))
// 				i++;
// 			count++;
// 		}
// 	}
// 	return (count);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*input;
// 	t_list		*temp;
// 	t_mini		mini;
// 	t_general	data_gen;
// 	int			flag;

// 	flag = 0;
// 	input = NULL;
// 	temp = NULL;
// 	ft_memset(&temp, 0, sizeof(temp));
// 	ft_memset(&mini, 0, sizeof(t_mini));
// 	ft_memset(&data_gen, 0, sizeof(t_general));
// 	(void)argv;
// 	(void)envp;
// 	if (argc < 1)
// 		return (1);
// 	g_exit_status = 0;
// 	mini.first_node = NULL;
// 	mini.total_nodes = 0;
// 	init_env_list(&mini, envp);
// 	ctrls(0);
// 	while (1)
// 	{
// 		input = readline("minishell -> ");
// 		if (input == NULL)
// 			break ;
// 		if (*input != '\0')
// 		{
// 			add_history(input);
// 			if (comprove_input(input) == 1)
// 			{
// 				printf("imput no valido\n");
// 				g_exit_status = 2;
// 				free(input);
// 			}
// 			else
// 			{
// 				if (num_pipes(input, '|') != 0)
// 					temp = asigg_cont_list(mat_to_list(ft_split_quotes(input,
// 									'|')), &data_gen, &mini);
// 				else
// 				{
// 					node_to_end(&temp, new_doble_node(input));
// 					temp = asigg_cont_list(temp, &data_gen, &mini);
// 				}
// 				// print_cmd_list(temp);
// 				if (temp)
// 				{
// 					if (comprove_heredocs(temp) == -1)
// 						close_herdocs(temp, &data_gen);
// 					else
// 					{
// 						if (num_pipes(input, '|') == 0
// 							&& is_builting(temp->cmd_path))
// 						{
// 							if (try_to_open_all_fds(temp) == 0)
// 								execute_builtin_with_redir(temp, &data_gen,
// 									&mini);
// 							close_herdocs(temp, &data_gen);
// 						}
// 						else
// 						{
// 							execute_list(temp, data_gen, &mini);
// 							close_herdocs(temp, &data_gen);
// 						}
// 					}
// 					free_list(&temp);
// 					free_env_array(data_gen.my_env);
// 					data_gen.my_env = NULL;
// 				}
// 				else
// 				{
// 					ft_free_mat_void((void **)data_gen.my_env,
// 						ft_matlen(data_gen.my_env));
// 					ft_free_mat_void((void **)data_gen.pipes, (list_size(&temp))
// 						- 1);
// 					ft_free_array_void(data_gen.pids);
// 					free_list(&temp);
// 				}
// 				free(input);
// 			}
// 		}
// 	}
// 	free_all(&mini);
// 	return (0);
// }