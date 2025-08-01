/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:37:50 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/08 13:16:15 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_ptr(unsigned long long address, int *num_char, int *error)
{
	static char	hex_array[16] = "0123456789abcdef";

	ft_putstr_we("0x", num_char, error);
	if (*error == -1)
		return ;
	if (address != 0)
	{
		ft_putstr_we("0x", num_char, error);
		if (*error == -1)
			return ;
	}
	if (address < 16)
	{
		ft_putchar_we(hex_array[address], num_char, error);
		return ;
	}
	else
	{
		print_hex_lower(address / 16, num_char, error, 0);
		if (*error == -1)
			return ;
	}
	ft_putchar_we(hex_array[address % 16], num_char, error);
	return ;
}
