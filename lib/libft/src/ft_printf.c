/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:47:47 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/08 12:16:36 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_conversion(const char *format, va_list *ap,
	int *num_char, int *error)
{
	if (*format == 'c' || *format == '%')
		ft_putchar_we(va_arg(*ap, int), num_char, error);
	else if (*format == 's')
		ft_putstr_we(va_arg(*ap, char *), num_char, error);
	else if (*format == 'p')
		print_ptr(va_arg(*ap, unsigned long long), num_char, error);
	else if (*format == 'd' || *format == 'i')
		ft_putnbr_we(va_arg(*ap, int), num_char, error, 0);
	else if (*format == 'u')
		print_unsigned_int(va_arg(*ap, unsigned int), num_char, error);
	else if (*format == 'x')
		print_hex_lower(va_arg(*ap, unsigned int), num_char, error, 0);
	else if (*format == 'X')
		print_hex_upper(va_arg(*ap, unsigned int), num_char, error, 0);
	else
		ft_putchar_we(*format, num_char, error);
}

void	print_with_format(const char *format, va_list *ap,
							int *num_char, int *error)
{
	while (*format && *error != -1)
	{
		if (*format != '%')
			ft_putchar_we(*format, num_char, error);
		else
		{
			format++;
			if (!*format)
				return ;
			if (is_a_conversion(format))
				print_conversion(format, ap, num_char, error);
			else if (is_a_valid_flag(format))
				print_with_flag(format, ap, num_char, error);
			else
				ft_putchar_we(*format, num_char, error);
		}
		format++;
	}
}

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	int			num_char;
	int			error;

	if (!format)
		return (-1);
	va_start(ap, format);
	num_char = 0;
	error = 0;
	print_with_format(format, &ap, &num_char, &error);
	va_end(ap);
	if (error == -1)
		return (-1);
	return (num_char);
}
