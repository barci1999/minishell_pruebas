#ifndef PRUEBAS_H
# define PRUEBAS_H

# include<unistd.h>
# include<stdio.h>
# include<readline/readline.h>
# include <readline/history.h>
# include"libft.h"
# include "ft_printf.h"

typedef enum e_token_type {
    CMD,        // Comando (por ejemplo, 'ls', 'cat', etc.)
    ARG,        // Argumento de un comando (por ejemplo, 'archivo.txt', 'directorio', etc.)
    PIPE,       // Operador pipe '|'
    REDIR_IN,   // Redirección de entrada '<'
    REDIR_OUT,  // Redirección de salida '>'
    REDIR_APPEND, // Redirección de salida en modo append '>>'
    HEREDOC,    // Redirección de entrada con delimitador '<<'
    ENV_VAR,    // Variables de entorno, por ejemplo '$HOME'
    DOLLAR_EXIT, // Expansión de $? para el estado de salida
    QUOTE,      // Comillas simples (') o dobles (")
    INVALID     // Token inválido o no reconocido
} t_token_type;

typedef enum e_signal_type {
    SIG_INT,    // CTRL+C (Interrupción)
    SIG_QUIT,   // CTRL+\ (Quit)
    SIG_EOF,    // CTRL+D (Fin de archivo)
    SIG_NONE    // Sin señal
} t_signal_type;

typedef enum e_builtin_type {
    ECHO,       // Comando echo con opción -n
    CD,         // Comando cd con rutas absolutas o relativas
    PWD,        // Comando pwd
    EXPORT,     // Comando export
    UNSET,      // Comando unset
    ENV,        // Comando env
    EXIT,       // Comando exit
    BUILTIN_NONE // No es un comando interno
} t_builtin_type;

typedef enum e_exec_status {
    EXEC_SUCCESS,  // Ejecución exitosa
    EXEC_FAILURE,  // Fallo en la ejecución
    EXEC_RUNNING,  // Comando en ejecución
    EXEC_EXIT      // Terminación del shell (exit)
} t_exec_status;

typedef enum e_expansion_type {
    EXPAND_NONE,       // No expansión
    EXPAND_ENV_VAR,    // Expansión de variable de entorno (por ejemplo, $HOME)
    EXPAND_EXIT_STATUS, // Expansión de $? (estado de salida)
    EXPAND_UNKNOWN     // Expansión desconocida o no válida
} t_expansion_type;

typedef struct t_list
{
	void			*content;
	struct t_list	*next;
}t_list;

void	print_list(t_list *list);
t_list				*ft_lstnew(void *content);
void				ft_lstadd_back(t_list **lst, t_list *new);
void parse_split(char **matrix);
t_list	*ft_lstlast(t_list *lst);
t_token_type classify_tokken(char *token);
void tonkenize(char *input);
#endif
