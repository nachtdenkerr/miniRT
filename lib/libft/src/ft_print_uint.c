/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:37:54 by thudinh           #+#    #+#             */
/*   Updated: 2025/03/19 16:27:46 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_unsigned_int(unsigned int num, int *num_char, int *error)
{
	if (num < 10)
	{
		ft_putchar_we(num + '0', num_char, error);
		return ;
	}
	else
	{
		ft_putnbr_we(num / 10, num_char, error, 0);
		if (*error == -1)
			return ;
	}
	ft_putchar_we((num % 10) + '0', num_char, error);
	return ;
}
