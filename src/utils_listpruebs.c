#include"pruebas.h"

void	print_list(t_list *list)
{
	t_list	*now;

	now = list;
	while (now)
	{
		ft_printf("%s\n", now->content);
		now = now->next;
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;
	new_node = malloc(1 * sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!*lst || !new)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast(*lst);
	temp->next = new;
}
t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
