NAME	= mini

CC	= cc

# Opciones de compilación (solo para compilar .c a .o)
CFLAGS = -Wall -Werror -Wextra -g3 -I./include -I libft -I printf

# Directorios de las bibliotecas
LIBFT_DIR = ./libft
PRINT_DIR = ./printf

# Librerías necesarias para el enlazado
LIBS = -L$(LIBFT_DIR) -lft -L$(PRINT_DIR) -lftprintf -lreadline

# Archivos fuente
SRCS =  src/main.c\
		src/utils_doble_list.c\
		src/utils_asigg_node_var.c\
		borrar.c\
		src/utils_env.c\
		src/counters.c\
		src/ctrls.c\
		src/utils_asigg_node_var_2.c\
		src/detectors.c\
		src/detectors_2.c\
		src/heredocs.c\
		src/execution.c\
		src/expand_str.c\
		src/redirections.c\
		src/procces.c\
		src/enviroment/utils_enviroment.c\
		src/builtings/echo.c\
		src/builtings/export.c\
		src/builtings/utils_export.c\
		src/builtings/utils_export_2.c\
		src/builtings/env.c\
		src/builtings/pwd.c\
		src/builtings/cd.c\
		src/builtings/exit.c\
		src/builtings/unset.c\
		src/enviroment/utils_enviroment_2.c\
		src/status_redirecc.c\
		src/assig_nodes_var.c\
		src/quotes.c\
		


# Archivos objeto
OBJS = $(SRCS:.c=.o)

# Regla por defecto: compilar y enlazar
all: $(NAME)

# Regla para crear el ejecutable
$(NAME): $(OBJS)
	make -s -C $(PRINT_DIR)
	make -s -C $(LIBFT_DIR)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(NAME)

# Regla para compilar los archivos .c a .o
%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

# Regla de limpieza (eliminar objetos .o)
clean:
	rm -f $(OBJS)
	make -s -C $(LIBFT_DIR) clean
	make -s -C $(PRINT_DIR) clean

# Regla de limpieza total (eliminar ejecutables y objetos .o)
fclean: clean
	make -s -C $(LIBFT_DIR) fclean
	make -s -C $(PRINT_DIR) fclean
	rm -f $(NAME)

# Regla para reconstruir todo
re: fclean all

.PHONY: all clean fclean re