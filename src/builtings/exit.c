/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksudyn <ksudyn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:37:07 by pablalva          #+#    #+#             */
/*   Updated: 2025/05/22 20:49:27 by ksudyn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pruebas.h"

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
	// if (digit > LLONG_MAX + sign)
	// 	return (0);
	// *result = (long long)digit - sign;
	*result = digit * sign;
	return (1);
}

// static int	final_numbers(char *str, long long *result)
// {
// 	long long	number;
// 	int			i;

// 	i = 0;
// 	if (str[i] == '\0')
// 		return (0);
// 	if (transform_number(str, &number) == 0)
// 		return (0);
// 	if (str[i] == '-')
// 	{
// 		number = number + 1;
// 		*result = -number;
// 	}
// 	else
// 		*result = number;
// 	return (1);
// }

static int final_numbers(char *str, long long *result)
{
	if (str[0] == '\0')
		return (0);
	return transform_number(str, result);
}

// static int	multiple_args(char **exit_args, int argc)
// {
// 	long long	exit_code;
// 	char		*trimmed_arg;

// 	trimmed_arg = ft_strtrim(exit_args[1], " \f\r\n\t\v");
// 	if (!trimmed_arg)
// 		return (2);
// 	if (final_numbers(trimmed_arg, &exit_code) == 0)
// 	{
// 		printf("exit\n");
// 		printf("minishell: exit: %s: numeric argument required\n",
// 			exit_args[1]);
// 		free(trimmed_arg);
// 		return (2);
// 	}
// 	//final_numbers(trimmed_arg, &exit_code);
// 	free(trimmed_arg);
// 	if (argc > 2)
// 	{
// 		printf("exit\n");
// 		printf("minishell: exit: too many arguments\n");
// 		return (-1);
// 	}
// 	return (exit_code % 256);
// }

static int multiple_args(char **exit_args, int argc)
{
    long long exit_code;
    char *trimmed_arg;

    trimmed_arg = ft_strtrim(exit_args[1], " \f\r\n\t\v");
    if (!trimmed_arg)
        return (2);

    if (final_numbers(trimmed_arg, &exit_code) == 0)
    {
        printf("exit\n");
        printf("minishell: exit: %s: numeric argument required\n",
            exit_args[1]);
        free(trimmed_arg);
        return (2);
    }
    free(trimmed_arg);
    if (argc > 2)
    {
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
        return (-1);
    }
	printf("[multiple_args] exit_code raw = %lld\n", exit_code);
    return ((exit_code % 256) + 256) % 256;
}


int	ft_exit(char **exit_args)
{
	int	i;
	int	exit_status;

	i = 0;
	while (exit_args[i])
		i++;
	if (i == 1)
	{
		printf("se ha usado mi exit\n");
		exit(0);
	}
	exit_status = multiple_args(exit_args, i);
	if (exit_status == -1)
	{
		printf("se ha usado mi exit pero no sale por muchos argumentos\n");
		return (1);
	}
	printf("se ha usado mi exit con numeros\n");
	printf("[ft_exit] exit_status = %d\n", exit_status);
	exit(exit_status);
}