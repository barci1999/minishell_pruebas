/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_sintax3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pablalva <pablalva@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-03-19 22:25:25 by pablalva          #+#    #+#             */
/*   Updated: 2025-03-19 22:25:25 by pablalva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"pruebas.h"

void fun_error_sintax(t_list **list)
{
	free_list(list);
	ft_putendl_fd("Sintax Error",2);
	exit(2);
}