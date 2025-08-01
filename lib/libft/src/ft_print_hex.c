/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:37:41 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/08 13:16:13 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hex_lower(unsigned int num, int *num_char,
						int *error, int flag)
{
	static char	hex_array[16] = "0123456789abcdef";

	if (flag && num != 0)
	{
		ft_putstr_we("0x", num_char, error);
		if (*error == -1)
			return ;
		flag = 0;
	}
	if (num < 16)
	{
		ft_putchar_we(hex_array[num], num_char, error);
		return ;
	}
	else
	{
		print_hex_lower(num / 16, num_char, error, flag);
		if (*error == -1)
			return ;
	}
	ft_putchar_we(hex_array[num % 16], num_char, error);
	return ;
}

void	print_hex_upper(unsigned int num, int *num_char,
						int *error, int flag)
{
	static char	hex_array[16] = "0123456789ABCDEF";

	if (flag && num != 0)
	{
		ft_putstr_we("0X", num_char, error);
		if (*error == -1)
			return ;
		flag = 0;
	}
	if (num < 16)
	{
		ft_putchar_we(hex_array[num], num_char, error);
		return ;
	}
	else
	{
		print_hex_upper(num / 16, num_char, error, flag);
		if (*error == -1)
			return ;
	}
	ft_putchar_we(hex_array[num % 16], num_char, error);
	return ;
}
