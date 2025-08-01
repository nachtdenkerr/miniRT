/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:22:58 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/08 12:16:04 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_hex_flag(const char *format, va_list *ap,
						int *num_char, int *error)
{
	while (*format == '#')
		format += 1;
	if (*format == 'x')
		print_hex_lower(va_arg(*ap, unsigned int), num_char, error, 1);
	else if (*format == 'X')
		print_hex_upper(va_arg(*ap, unsigned int), num_char, error, 1);
	if (*error == -1)
		return ;
}

void	print_space_sign_flag(const char *format, va_list *ap,
								int *num_char, int *error)
{
	int	flag_sign;

	flag_sign = 2;
	while (*format == ' ' || *format == '+')
	{
		if (*format == '+')
			flag_sign = 1;
		format += 1;
	}
	if (*format == 'd' || *format == 'i')
		ft_putnbr_we(va_arg(*ap, int), num_char, error, flag_sign);
	else if (*format == 's' && flag_sign == 2)
		ft_putstr_we(va_arg(*ap, char *), num_char, error);
	else
		*error = -1;
}

void	print_with_flag(const char *format, va_list *ap,
						int *num_char, int *error)
{
	if (*format == '#')
		print_hex_flag(format, ap, num_char, error);
	else if (*format == ' ' || *format == '+')
		print_space_sign_flag(format, ap, num_char, error);
	if (*error == -1)
		return ;
}
