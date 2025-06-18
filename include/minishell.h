/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:45:53 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/18 17:53:42 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <wait.h>

extern int			g_exit_status;

typedef struct s_general
{
	char			**my_env;
	int				tem_heredoc;
	pid_t			*pids;
	int				**pipes;
	int				pipe_index;
	int				total_cmd;

}					t_general;

typedef enum e_token_type
{
	PIPE,
	STD_IN,
	HEREDOC,
	FD,
	STD_OUT,
	FD_APPEND,
}					t_token_type;
typedef enum e_status_tyoe
{
	CMD,
	REDIREC,
	WORD,
	OK,
	SYN_ERROR,
	MALLOC_ERROR,
}					t_status_type;

typedef struct t_list
{
	char			*content;
	char			*cmd_path;
	char			**cmd_arg;
	char			*cmd_name;
	char			**redirecc;
	char			**fd;
	char			**delim;
	int				order;
	char			*variable;
	struct t_list	*next;
	struct t_list	*prev;

}					t_list;

typedef struct s_mini
{
	t_list			*first_node;
	t_list			*node_inter;
	int				total_nodes;
}					t_mini;

typedef struct s_quotes
{
	char			*src;
	char			**result;
	char			**result_base;
	int				*i;
	int				*m;
}					t_quotes;

// Apunta al primer nodo de la lista de variables de entorno
// Iterador temporal para recorrer la lista
// Número total de variables en la lista

/*    funciones ctrls      */
void				ctrls(int is_child);
void				ctrl_child(int signal);
void				ctrl_minishell(int signal);
void				execute_builting(t_list *node, t_mini *mini);
int					ft_echo(char **args);
int					ft_export(char **args, t_mini *mini);
int					export_args(char **args, t_mini *mini);
void				export_error(char *var);
int					print_single_export(t_list *node);
void				nodes_order(t_mini *mini);
void				add_or_update_variable(t_mini *mini, char *var,
						char *value);
t_list				*new_node_export(char *var, char *value);
int					is_valid_variable_export(char *var);
int					ft_env(char **args, t_mini *mini);
int					ft_pwd(void);
void				new_pwd(char *new_path);
void				previous_pwd(void);
int					ft_cd(char **args);
int					ft_exit(char **exit_args);
int					ft_unset(char **args, t_mini *mini);
t_list				*create_env_node(char *var, char *value);
void				add_env_var(t_mini *mini, char *var, char *value);
void				init_env_list(t_mini *mini, char **envp);
void				free_env_list(t_mini *mini);
char				**env_list_to_array(t_mini *mini);
char				*build_env_string(t_list *node);
void				free_env_array(char **envp);
void				print_cmd_list(t_list *list);
void				free_list(t_list **list);
int					node_to_end(t_list **list, t_list *insert);
t_list				*new_doble_node(char *token);
size_t				list_size(t_list **list);
int					comprove_heredocs(t_list *list);
int					open_all_herdocs(t_list *list);
int					open_the_heredoc(t_list *list, int redir_index,
						int delim_index);
void				close_herdocs(t_list *list, t_general *gen);
void				open_and_redir_out(t_list *node, t_general *general, int i,
						int total_comds);
void				open_and_redir_in(t_list *node, t_general *general, int i);
t_status_type		mod_redir_and_fd(t_list *list, char **mat_content, int *i,
						t_general *data_gen);
t_status_type		handle_fd_redir(t_list *list, char **mat_content, int *i);
t_status_type		handle_heredoc(t_list *list, char **mat_content, int *i,
						t_general *data_gen);
t_status_type		handle_quoted_heredoc(t_list *list, char **mat_content,
						int *i);
t_status_type		handle_simple_heredoc(t_list *list, char **mat_content,
						int *i);
void				execute_list(t_list *list, t_general general, t_mini *mini);
void				execute_builtin_with_redir(t_list *node,
						t_general *data_gen, t_mini *mini);
void				close_all_pipes(int total_cmds, t_general *general);
void				wait_all_procces(t_general *general, int i);
pid_t				*gen_pid_array(size_t nbr_proces);
int					**gen_pipes_array(size_t n_cmd);
int					is_builting(char *token);
int					have_a_heredoc(t_list *node);
int					is_redirec(char *str);
int					is_cmd(char *comprove, t_general *data_gen);
t_token_type		identify_reddir_in(t_list *node);
t_token_type		iden_red_out(t_list *node);
int					return_fd_in(t_list *node);
int					return_fd_out(t_list *node);
t_status_type		update_status(char **math_content, int *i,
						t_general *data_gen);
int					is_operator_char(char c);
int					dir_exists(const char *filepath);
bool				nbr_quotes_ok(char *src);
size_t				nb_redirrec(char **mat);
size_t				num_pipes(char *input, char c);
char				**take_paths_env(char **envp);
char				*take_cmd_path(char *comprove, t_general *data_gen);
t_list				*mat_to_list(char **mat);
t_list				*asigg_cont_list(t_list *list, t_general *data_gen,
						t_mini *mini);
char				**assig_redirecc(char **mat, t_list *list);
char				**assig_fd(char **mat, t_general *data_gen, t_list *list);
char				**assig_delim(char **mat, t_list *list);
char				*asigg_cmd_name(char *cmd_path, t_list *list);
char				*take_cmd_path(char *comprove, t_general *data_gen);
int					is_quote(char c);
char				*add_expand_str(t_mini *mini, char *src, char *matrix,
						int *i);
int					count_nodes(t_mini *mini);
int					assig_var_node(char **math_content, t_list *list,
						t_general *data_gen);
t_status_type		safe_add_str(char ***mat, char *str);
t_status_type		mod_cmd_and_args(t_list *list, char **math_content, int *i,
						t_general *data_gen);
char				**add_str_to_mat(char **src, char *to_add);
char				*take_the_redir(char **str);
char				*add_chr_to_str(char *src, char c);
size_t				number_of_cmd_arg(const char *src);
char				*get_env_value(t_mini *mini, char *var_name);
void				no_quote(t_quotes *quot, t_mini *mini);
void				doble_quote(t_quotes *quot, t_mini *mini);
char				**fukking_quotes(char *src, t_mini *mini);
void				single_quote(t_quotes *quot);
void				evalue_next_char(t_quotes *quot);
void				evalue_next_char(t_quotes *quot);
char				*take_the_expand(char *src, int *i, t_mini *mini);
char				*ft_free_strjoin(char *s1, char *s2);
void				print_cmd_error(char *cmd, char *msg, int code);
int					try_to_open_all_fds(t_list *node);
void				free_all(t_mini *mini);
void				close_unused_pipes(int pipe_index, int total_cmds,
						int **pipes);
void				handle_external_command(t_list *node, t_general *general);
void				execute_builting(t_list *node, t_mini *mini);
char				**remove_nulls(char **matrix, int strings);
int					middle_null(char **result, int strings);
void				execute_node(t_list *node, t_general *general, t_mini *mini,
						t_list **lista);
void				end_exec(t_list *list, t_general *general, int i);
void				handle_parent(pid_t pid, t_general *gen, int *i);
void				handle_child(t_list *node, t_general *gen, t_mini *mini,
						t_list *list);
void				redir_and_exec(t_list *node, t_general *gen, t_mini *mini,
						t_list *list);
void				init_exec_data(t_list **list, t_general *general);
t_status_type	handle_complex_redir(t_list *list, char **mat, int *i);
t_status_type	handle_simple_redir(t_list *list, char **mat, int *i);
t_status_type	handle_quoted_heredoc(t_list *list, char **mat_content, int *i);
t_status_type	handle_simple_heredoc(t_list *list, char **mat_content, int *i);
void print_perror_exit(char *msg, int code);
void	print_cmd_error_exit(char *cmd, char *msg, int code);
#endif