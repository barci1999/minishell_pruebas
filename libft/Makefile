# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pablalva <pablalva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 10:29:24 by pablalva          #+#    #+#              #
#    Updated: 2025/05/31 16:08:51 by pablalva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc

CFILES = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c\
       ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c\
       ft_strchr.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c\
       ft_strrchr.c ft_tolower.c ft_toupper.c ft_calloc.c ft_strdup.c ft_substr.c\
	   ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c\
	   ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c\
	   ft_str_isdigit.c ft_atof.c ft_str_is_dec.c ft_del.c ft_atol.c\
		ft_is_sing.c ft_is_valid_num.c ft_sqrt.c get_next_line.c get_next_line_utils.c ft_matlen.c\
		ft_free_mat.c ft_strcmp.c ft_dup_mat.c ft_split_quotes.c ft_is_space.c ft_strndup.c\
		ft_free_mat_int.c\

HEADERS_DIR = /

OBJS = $(CFILES:.c=.o)

OBJS_B = $(BONUS:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g3 -I $(HEADERS_DIR)

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo "creando objetos..."
	
bonus: $(OBJS) $(OBJS_B)
	@ar rc $(NAME) $(OBJS) $(OBJS_B)
	@echo "creando objetos totales..."

clean:
	@rm -f $(OBJS) $(OBJS_B)
	@echo "limpiando los objetos..."

fclean: clean
	@rm -f $(NAME)
	@echo "limpiando $(NAME)"

re: fclean all

exe: all clean
	@./$(NAME)
	@rm -f $(NAME)

.PHONY: all clean fclean re exe
