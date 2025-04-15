
#include "pruebas.h"

void	print_cmd_list(t_list *list)
{
	int	i;
	int	j;

	i = 0;
	while (list)
	{
		printf("╔════════════════════════════════════════╗\n");
		printf("║              Nodo %d                    ║\n", i);
		printf("╠════════════════════════════════════════╣\n");
		printf("║ content   : %-26s ║\n",
			list->content ? list->content : "(null)");
		printf("║ cmd_path  : %-26s ║\n",
			list->cmd_path ? list->cmd_path : "(null)");
		printf("║ cmd_name  : %-26s ║\n",
			list->cmd_name ? list->cmd_name : "(null)");
		printf("╠════════════════════════════════════════╣\n");
		printf("║ cmd_arg   :                            ║\n");
		if (list->cmd_arg)
		{
			j = 0;
			while (list->cmd_arg[j++])
				printf("║    [%d] -> %-26s ║\n", j, list->cmd_arg[j]);
		}
		else
			printf("║    (null)                              ║\n");
		printf("╚════════════════════════════════════════╝\n\n");
		list = list->next;
		i++;
	}
}
