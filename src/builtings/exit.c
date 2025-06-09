/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:37:07 by pablalva          #+#    #+#             */
/*   Updated: 2025/06/09 17:43:05 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_long_number(char *str)
{
	unsigned long long	result;
	int					sign;
	int					i;
	int					digit;

	result = 0;
	sign = 0;
	i = 0;
	digit = 0;
	if (str[i] == '-')
		sign = 1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		digit = str[i] - '0';
		if (result > LLONG_MAX / 10 || (result == LLONG_MAX / 10
				&& digit > (LLONG_MAX % 10) + sign))
			return (0);
		result = result * 10 + digit;
		i++;
	}
	return (1);
}

static int	transform_number(char *str, long long *result)
{
	long long	digit;
	int			sign;
	int			i;

	digit = 0;
	sign = 1;
	i = 0;
	if (check_long_number(str) == 0)
		return (0);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i])
	{
		digit = digit * 10 + (str[i] - '0');
		i++;
	}
	*result = digit * sign;
	return (1);
}
// se quita el proceso de restar o sumar sign
// y pasa a una variable para despues multilpicar
// convirtiendo i en 1 o -1, (antes era 0 o 1)

static int	final_numbers(char *str, long long *result)
{
	if (str[0] == '\0')
		return (0);
	return (transform_number(str, result));
}
// como ya no se requiere hacer la suma de 1 por el signo se retira el if
// y el else,
// junto a sus respectivas variebles necesarias (number e i)
// reduciendo la funcion a una comprobacion de si str es NULL y el llamar a
// transformer_numbers

static int	multiple_args(char **exit_args, int argc)
{
	long long	exit_code;
	char		*trimmed_arg;

	trimmed_arg = ft_strtrim(exit_args[1], " \f\r\n\t\v");
	if (!trimmed_arg)
		return (2);
	if (final_numbers(trimmed_arg, &exit_code) == 0)
	{
		write(1, "exit\n", 5);
		write(2, "minishell: exit: ", 18);
		write(2, exit_args[1], ft_strlen(exit_args[1]));
		write(2, ": numeric argument required\n", 29);
		free(trimmed_arg);
		exit(2);
	}
	free(trimmed_arg);
	if (argc > 2)
	{
		write(1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
		g_exit_status = 1;
		return (-1);
	}
	return (((exit_code % 256) + 256) % 256);
}

// se quita el final_numbers(trimmed_arg, &exit_code); enciam del
// free(trimmed_arg, &exit_code)
// y se mejora el return (añadiendo + 256 ) %256);
// de esta forma ya no hay que gestionar el signo anteriormente
// si es 42 pasa esto (42 % 256) + 256 = 42 + 256 = 298
// 							298 % 256 = 42
// y con - 10 pasa esto (-10 % 256) = -10
// 						-10 + 256 = 246
// 						246 % 256 = 246 ✅
// asi se asegura de dar el codigo de salida correcto

int	ft_exit(char **exit_args)
{
	int	i;
	int	exit_status;

	i = 0;
	while (exit_args[i])
		i++;
	write(1, "exit\n", 5);
	if (i == 1)
		exit(g_exit_status);
	exit_status = multiple_args(exit_args, i);
	if (exit_status == -1)
	{
		return (1);
	}
	exit(exit_status);
}
// printf("se ha usado mi exit con numeros\n");
// printf("[ft_exit] exit_status = %d\n", exit_status);
// con estos cambios es mas legible y funciona correctamente los LLONG_MIN
// y LLONG_MAX
// y diferentes numeros entre medias y si se sale de estos numeros da el codigo
// de error correcto