
#include "pruebas.h"



#define WIDTH 48
#define WIDTH_2 48
#define WIDTH_3 48

// Función auxiliar para limpiar strings (quita \n, \t, etc.)
void sanitize_string(const char *src, char *dest, int max_len)
{
    int i = 0;
    while (*src && i < max_len - 1)
    {
        if (*src == '\n' || *src == '\t' || *src < 32)
            dest[i++] = ' ';
        else
            dest[i++] = *src;
        src++;
    }
    dest[i] = '\0';
}

// Imprime una línea del cuadro, asegurando longitud exacta
void print_box_line(const char *prefix, const char *value)
{
    char clean_value[256];
    char full[WIDTH + 1];
    char buffer[WIDTH + 1];

    sanitize_string(value ? value : "(null)", clean_value, sizeof(clean_value));

    snprintf(full, sizeof(full), "%s: %s", prefix, clean_value);

    if ((int)strlen(full) > WIDTH)
        snprintf(buffer, sizeof(buffer), "%.*s", WIDTH, full);
    else
        snprintf(buffer, sizeof(buffer), "%-*s", WIDTH, full);

    printf("║%s║\n", buffer);
}

// Función para imprimir la lista de comandos
void print_cmd_list(t_list *list)
{
    int i = 0;
    int j;
    int r;
    int f;
    while (list)
    {
        // Línea superior
        printf("╔════════════════════════════════════════════════╗\n");

        // Imprimir título del nodo
        char title[WIDTH + 1];
        snprintf(title, sizeof(title), "Nodo %d", i);
        printf("║%-*s║\n", WIDTH, title);

        // Línea de separación
        printf("╠════════════════════════════════════════════════╣\n");

        // Imprimir contenido
        print_box_line("content", list->content);
        print_box_line("cmd_path", list->cmd_path);
        print_box_line("cmd_name", list->cmd_name);

        // Línea de separación
        printf("╠════════════════════════════════════════════════╣\n");

        // Imprimir argumentos de comandos
        print_box_line("cmd_arg", "");

        if (list->cmd_arg)
        {
            j = 0;
            while (list->cmd_arg[j])
            {
                char clean_arg[256];
                char arg_line[WIDTH + 1];
                char output[WIDTH + 1];

                sanitize_string(list->cmd_arg[j], clean_arg, sizeof(clean_arg));
                snprintf(arg_line, sizeof(arg_line), "   [%d] -> %s", j, clean_arg);

                if ((int)strlen(arg_line) > WIDTH)
                    snprintf(output, sizeof(output), "%.*s", WIDTH, arg_line);
                else
                    snprintf(output, sizeof(output), "%-*s", WIDTH, arg_line);

                printf("║%s║\n", output);
                j++;
            }
            char final_line[WIDTH + 1];
            snprintf(final_line, sizeof(final_line), "   [%d] -> (null)", j);
            printf("║%-*s║\n", WIDTH, final_line);
        }
        printf("╠════════════════════════════════════════════════╣\n");
        print_box_line("redirects", "");
        if(list->redirecc)
        {
            r = 0;
            while(list->redirecc[r])
            {
                char clean_red[256];
                char red_line[WIDTH_2 + 1];
                char output_red[WIDTH_2 + 1];

                sanitize_string(list->redirecc[r], clean_red, sizeof(clean_red));
                snprintf(red_line, sizeof(red_line), "   [%d] -> %s", r, clean_red);

                if ((int)strlen(red_line) > WIDTH_2)
                    snprintf(output_red, sizeof(output_red), "%.*s", WIDTH_2, red_line);
                else
                    snprintf(output_red, sizeof(output_red), "%-*s", WIDTH_2, red_line);

                printf("║%s║\n", output_red);
                r++;
            }
            char final_red[WIDTH_2 + 1];
            snprintf(final_red, sizeof(final_red), "   [%d] -> (null)", r);
            printf("║%-*s║\n", WIDTH_2, final_red);
        }
        else
        {
            printf("║%-*s║\n", WIDTH_2, "   (null)");
        }
        printf("╠════════════════════════════════════════════════╣\n");
        print_box_line("fd", "");
        if(list->fd)
        {
            f = 0;
            while (list->fd[f])
            {
                char clean_fd[256];
                char fd_line[WIDTH_3 + 1];
                char output_fd[WIDTH_3 + 1];

                sanitize_string(list->fd[f], clean_fd, sizeof(clean_fd));
                snprintf(fd_line, sizeof(fd_line), "   [%d] -> %s", f, clean_fd);

                if ((int)strlen(fd_line) > WIDTH_3)
                    snprintf(output_fd, sizeof(output_fd), "%.*s", WIDTH_3, fd_line);
                else
                    snprintf(output_fd, sizeof(output_fd), "%-*s", WIDTH_3, fd_line);

                printf("║%s║\n", output_fd);
                f++;
            }
            char final_fd[WIDTH_3 + 1];
            snprintf(final_fd, sizeof(final_fd), "   [%d] -> (null)", f);
            printf("║%-*s║\n", WIDTH, final_fd);
        }
        else
        {
            printf("║%-*s║\n", WIDTH_3, "   (null)");
        }
        
        //print_box_line("fd", list->fd);
        // Línea final
        printf("╠════════════════════════════════════════════════╣\n");
        print_box_line("delim", list->delim);
        printf("╚════════════════════════════════════════════════╝\n\n");

        list = list->next;
        i++;
    }
}
