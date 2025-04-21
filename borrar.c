
#include "pruebas.h"



#define WIDTH 48

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
        else
        {
            printf("║%-*s║\n", WIDTH, "   (null)");
        }
        printf("╠════════════════════════════════════════════════╣\n");
        print_box_line("redirect", list->redirecc);
        print_box_line("delim", list->delim);

        print_box_line("fd", list->fd);
        // Línea final
        printf("╚════════════════════════════════════════════════╝\n\n");

        list = list->next;
        i++;
    }
}
