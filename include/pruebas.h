#ifndef PRUEBAS_H
# define PRUEBAS_H

# include<unistd.h>
# include<stdio.h>
# include<readline/readline.h>
# include <readline/history.h>
# include"libft.h"
# include "ft_printf.h"

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

#endif