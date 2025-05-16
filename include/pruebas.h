/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:45:53 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/16 15:16:48 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRUEBAS_H
# define PRUEBAS_H

# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>
# include <wait.h>

typedef struct s_general
{
	char		**my_env;
	int			tem_heredoc;
	pid_t		*pids;
	int			**pipes;
	int			last_exit_code;

}				t_general;

typedef enum e_token_type
{
	PIPE,    // Operador pipe '|'
	STD_IN,  // Redirección de entrada '<'
	HEREDOC, // Redirección de entrada con delimitador '<<'
	FD,      // entrada de la redireccion
	STD_OUT,
	FD_APPEND,
}				t_token_type;

typedef enum e_signal_type
{
	SIG_INT,  // CTRL+C (Interrupción)
	SIG_QUIT, // CTRL+\ (Quit)
	SIG_EOF,  // CTRL+D (Fin de archivo)
	SIG_NONE  // Sin señal
}				t_signal_type;

typedef enum e_builtin_type
{
	ECHO,        // Comando echo con opción -n
	CD,          // Comando cd con rutas absolutas o relativas
	PWD,         // Comando pwd
	EXPORT,      // Comando export
	UNSET,       // Comando unset
	ENV,         // Comando env
	EXIT,        // Comando exit
	BUILTIN_NONE // No es un comando interno
}				t_builtin_type;

typedef enum e_exec_status
{
	EXEC_SUCCESS, // Ejecución exitosa
	EXEC_FAILURE, // Fallo en la ejecución
	EXEC_RUNNING, // Comando en ejecución
	EXEC_EXIT     // Terminación del shell (exit)
}				t_exec_status;

typedef enum e_expansion_type
{
	EXPAND_NONE,        // No expansión
	EXPAND_ENV_VAR,     // Expansión de variable de entorno (por ejemplo, $HOME)
	EXPAND_EXIT_STATUS, // Expansión de $? (estado de salida)
	EXPAND_UNKNOWN      // Expansión desconocida o no válida
}				t_expansion_type;

typedef struct t_list
{
	t_token_type token;  // 1º paso           // 2º paso
	char *content;       // infile < cat -e  //  infile < cat -e
	char *cmd_path;      // NULL             //  /usr/bin/cat
	char **cmd_arg;      // NULL             //  infile | < | cat | -e
	char *cmd_name;      // NULL             //  cat
	char **redirecc;     // NULL             //  <
	char **fd;           // NULL             //  infile
	char **delim;        // NULL             //  EOF
	struct t_list *next; // siguiente nodo   //  siguiente nodo
	struct t_list *prev; // anterior nodo    //  anterior nodo

}				t_list;

/* funcciones a borrar  */

void			print_cmd_list(t_list *list);

/*    liberacion y errores  */

void			free_int_matrix(int **matrix, size_t len);

/* list fuctions      */

void			free_list(t_list **list);
int				node_to_end(t_list **list, t_list *insert);
t_list			*new_doble_node(char *token);
size_t			list_size(t_list **list);

/* heredocs functions */

void			comprove_heredocs(t_list *list);
void			open_all_herdocs(t_list *list);
void			open_the_heredoc(t_list *list, int redir_index,
					int delim_index);
					
/* redirection functions */
void	open_and_redir_out(t_list *node, t_general *general, int i);
void	open_and_redir_in(t_list *node, t_general *general, int i);

/* execution functions */

void			execute_list(t_list *list, t_general general);

/* procces function    */

pid_t			*gen_pid_array(size_t nbr_proces);
int				**gen_pipes_array(size_t n_cmd);

/* detectors           */

int				is_builting(char *token);
int				have_a_heredoc(t_list *node);
int				is_redirec(char *str);
int				is_cmd(char *comprove, t_general *data_gen);
t_token_type	identify_reddir_in(t_list *node);
t_token_type	identify_reddir_out(t_list *node);
int				return_fd_in(t_list *node);
int				return_fd_out(t_list *node);

/* counters */

bool			nbr_quotes_ok(char *src);
size_t			nb_redirrec(char **mat);
size_t			num_pipes(char *input, char c);

/* funciones env */
char			**take_paths_env(char **envp);
char			*take_cmd_path(char *comprove, t_general *data_gen);

/* funciones de asignacion de variables a los nodos */

t_list			*mat_to_list(char **mat);
t_list			*asigg_cont_list(t_list *list, t_general *data_gen);
char			**assig_redirecc(char **mat, t_list *list);
char			**assig_fd(char **mat, t_general *data_gen, t_list *list);
char			**assig_delim(char **mat, t_list *list);
char			*asigg_cmd_name(char *cmd_path, t_list *list);
char			**assig_cmd_args(char *cmd_name, char **mat, t_list *list);
char			*asig_cmd_path(char **mat_content, t_general *data_gen,
					t_list *list);
char			*take_cmd_path(char *comprove, t_general *data_gen);

#endif
