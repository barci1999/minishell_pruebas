/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 22:45:53 by pablalva          #+#    #+#             */
/*   Updated: 2025/04/16 17:07:14 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRUEBAS_H
# define PRUEBAS_H

# include "ft_printf.h"
# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/stat.h>

typedef struct s_general
{
    char **my_env;
    
}   t_general;


typedef enum e_token_type
{
    CMD,          // Comando (por ejemplo, 'ls', 'cat', etc.)
    ARG,          // Argumento de un comando (por ejemplo, 'archivo.txt','directorio', etc.)
    PIPE,         // Operador pipe '|'
    REDIR_IN,     // Redirección de entrada '<'
    REDIR_OUT,    // Redirección de salida '>'
    REDIR_APPEND, // Redirección de salida en modo append '>>'
    HEREDOC,      // Redirección de entrada con delimitador '<<'
    ENV_VAR,      // Variables de entorno, por ejemplo '$HOME'
    DOLLAR_EXIT,  // Expansión de $? para el estado de salida
    QUOTE,        // Comillas simples (') o dobles (")
    WORD,         // Token inválido o no reconocido
    FD,           // entrada de la redireccion
    BUILTIN,
    DELIM,
}                   t_token_type;

typedef enum e_signal_type
{
    SIG_INT,  // CTRL+C (Interrupción)
    SIG_QUIT, // CTRL+\ (Quit)
    SIG_EOF,  // CTRL+D (Fin de archivo)
    SIG_NONE  // Sin señal
}                   t_signal_type;

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
}                   t_builtin_type;

typedef enum e_exec_status
{
    EXEC_SUCCESS, // Ejecución exitosa
    EXEC_FAILURE, // Fallo en la ejecución
    EXEC_RUNNING, // Comando en ejecución
    EXEC_EXIT     // Terminación del shell (exit)
}                   t_exec_status;

typedef enum e_expansion_type
{
    EXPAND_NONE,        // No expansión
    EXPAND_ENV_VAR,     // Expansión de variable de entorno (por ejemplo, $HOME)
    EXPAND_EXIT_STATUS, // Expansión de $? (estado de salida)
    EXPAND_UNKNOWN      // Expansión desconocida o no válida
}                   t_expansion_type;

typedef struct t_list
{
    t_token_type    token;          // 1º paso           // 2º paso
    char            *content;   //  infile < cat -e // infile < cat -e
    char            *cmd_path;  // NULL             //  /usr/bin/cat
    char            **cmd_arg;  // NULL             // infile | < | cat | -e
    char            *cmd_name;  // NULL             // cat
    struct t_list   *next;      // siguiente nodo   // siguiente nodo
    struct t_list   *prev;      // anterior nodo    // anterior nodo

}                   t_list;

/* funcciones a borrar  */

void                print_cmd_list(t_list *list);

/* tokens functions  */
t_token_type        classify_tokken(char *token);
t_list              *tokenize(char *input);
void                change_word(t_list **list);
int                 is_builting(char *token);
int	                is_space(char c);

/* list fuctions  */
void                free_list(t_list **list);
int               node_to_end(t_list **list, t_list *insert);
t_list              *new_doble_node(char *token);
t_list              *ft_lstlast(t_list *lst);



t_list              *matrix_to_list(char **matrix);
t_list	            *asigg_cont_list(t_list * list,t_general *data_gen);

/* Sintax functions  */
void                sintax_list(t_list **list);
int                 sintax_heredoc(t_token_type type,t_list *comprove);
int                 sintax_env_var(t_token_type type,t_list *comprove);
int                 sintax_redir_in(t_token_type type ,t_list *comprove);
int                 sintax_fd(t_token_type type,t_list *comprove);
int                 sintax_cmd(t_token_type type,t_list *comprove);
int                 sintax_arg(t_token_type type,t_list *comprove);
int                 sintax_pipe(t_token_type type,t_list *comprove);
int                 sintax_redirs_out(t_token_type type,t_list *comprove);
int                 sintax_redir_in(t_token_type type,t_list *comprove);
int                 sintax_builting(t_token_type type, t_list *comprove);
void                fun_error_sintax(char *error,t_list **list);
int                 sintax_dollar_exit(t_token_type type, t_list *comprove);

/* Expand Vatriable  */

size_t              nb_of_quotes(char *input);
char                *rem_sin_quotes(char *input);
char                *expand_str(char *input);
char                *expand_var(char *input, size_t i, size_t j);

/* pruebas de funciones */
size_t              num_pipes(char *input);
void	            rem_space(char **input, int *i, int *j);
char	            **split_pipes(char *input);
int 	            in_quotes(char **input,int i, int j);
int                 is_quote(char c);

/* funciones env */
char	            **take_paths_env(char **envp);
char	            *asig_cmd_path(char **matrix_content,t_general *data_gen);
char	            *take_cmd_path(char *comprove, t_general *data_gen);
char	            **assig_cmd_args(char *cmd_name, char **matrix_content);
int                 is_cmd(char *comprove,t_general *data_gen);
#endif
