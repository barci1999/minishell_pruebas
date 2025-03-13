/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_with_quote.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-13 19:10:32 by pablalva          #+#    #+#             */
/*   Updated: 2025-03-13 19:10:32 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t count_tokens(char *str) {
    size_t count = 0;
    int in_single_quote = 0;  // Estado de las comillas simples
    int in_double_quote = 0;  // Estado de las comillas dobles
    int in_escape = 0;        // Estado de escape
    int in_token = 0;         // Estado de token

    while (*str) {
        // Si encontramos un carácter de escape
        if (*str == '\\' && !in_escape) {
            in_escape = 1;  // El siguiente carácter está escapado
        }
        // Si estamos dentro de comillas simples
        else if (*str == '\'' && !in_double_quote && !in_escape) {
            in_single_quote = !in_single_quote;  // Alternamos si estamos dentro de comillas simples
        }
        // Si estamos dentro de comillas dobles
        else if (*str == '\"' && !in_single_quote && !in_escape) {
            in_double_quote = !in_double_quote;  // Alternamos si estamos dentro de comillas dobles
        }
        // Si encontramos un espacio fuera de las comillas y sin escape
        else if (*str == ' ' && !in_single_quote && !in_double_quote && !in_escape) {
            if (in_token) {
                count++;  // Contamos el token
                in_token = 0;  // Fin del token
            }
        }
        // Si encontramos un carácter que no es espacio y no estamos escapando, iniciamos un nuevo token
        else if (*str != ' ' && !in_escape) {
            if (!in_token) {
                in_token = 1;  // Iniciamos un nuevo token
            }
        }

        // Si estamos escapando, marcamos que ya no estamos en estado de escape
        if (in_escape && (*str == ' ' || *str == '\'' || *str == '\"' || *str == '\\')) {
            in_escape = 0;  // Dejamos de estar en estado de escape
        }

        // No contar espacio después de barra invertida
        if (in_escape && *str == ' ') {
            in_escape = 0;  // No contamos el espacio, seguimos dentro del mismo token
        }

        // Si encontramos una comilla escapada dentro de comillas dobles, no la contamos como delimitador
        if (in_escape && in_double_quote && *str == '\"') {
            in_escape = 0;  // Desmarcamos el estado de escape para que no cierre la comilla
        }

        // Si llegamos al final de la cadena y las comillas no están cerradas, contamos el último token
        if (*str == '\0' && in_token) {
            count++;
        }

        str++;  // Avanzamos al siguiente carácter
    }

    // Si terminamos un token antes de llegar al final, lo contamos
    if (in_token) {
        count++;
    }

    return count;
}

int main() {
    // Pruebas
    //printf("Prueba 1: 'echo ls -l archivo.txt'\n");
    //printf("Número de tokens: %zu\n", count_tokens("echo ls -l archivo.txt"));

    //printf("Prueba 2: 'echo \"Hola mundo\"'\n");
    //printf("Número de tokens: %zu\n", count_tokens("echo \"Hola mundo\""));

    //printf("Prueba 3: 'echo 'Hola mundo''\n");
    //printf("Número de tokens: %zu\n", count_tokens("echo 'Hola mundo'"));

    printf("Prueba 4: 'echo \"Un texto con escape\\\" y más texto\"'\n");
    printf("Número de tokens: %zu\n", count_tokens("echo \"Un texto con escape\\\" y más texto\""));

    //printf("Prueba 5: '  echo    ls  -l   archivo.txt  '\n");
    //printf("Número de tokens: %zu\n", count_tokens("  echo    ls  -l   archivo.txt  "));

    //printf("Prueba 6: 'echo \"Hola mundo'\n");
    //printf("Número de tokens: %zu\n", count_tokens("echo \"Hola mundo"));

    //printf("Prueba 7: 'echo \"Texto con comillas escapadas \\\"correctamente\"'\n");
    //printf("Número de tokens: %zu\n", count_tokens("echo \"Texto con comillas escapadas \\\"correctamente\""));

    //printf("Prueba 8: 'echo'\n");
    //printf("Número de tokens: %zu\n", count_tokens("echo"));

    //printf("Prueba 9: 'echo 'Hello World'  '\n");
    //printf("Número de tokens: %zu\n", count_tokens("echo 'Hello World'  "));

    //printf("Prueba 10: 'echo 'Hola' \"Mundo\"'\n");
    //printf("Número de tokens: %zu\n", count_tokens("echo 'Hola' \"Mundo\""));

    printf("Prueba 11: 'echo Hello\\ World'\n");
    printf("Número de tokens: %zu\n", count_tokens("echo Hello\\ World"));

    return 0;
}



