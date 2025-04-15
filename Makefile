NAME	= mini

CC	= cc

# Opciones de compilación (solo para compilar .c a .o)
CFLAGS = -Wall -Werror -Wextra -I./include -I libft -I printf

# Directorios de las bibliotecas
LIBFT_DIR = ./libft
PRINT_DIR = ./printf

# Librerías necesarias para el enlazado
LIBS = -L$(LIBFT_DIR) -lft -L$(PRINT_DIR) -lftprintf -lreadline

# Archivos fuente
SRCS = src/main.c src/utils_doble_list.c src/utils_enums.c src/util_sintax.c src/utils_sintax2.c src/utils_sintax3.c\
		src/utils_expand_2.c src/utils_split_pipes.c pruebas_2.c borrar.c src/utils_env.c

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
%.o: %.c includes/pipex.h
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


