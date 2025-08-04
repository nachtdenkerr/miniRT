/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_flag.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:21:27 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/08 13:15:44 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_a_conversion(const char *format)
{
	if (*format == 'c' || *format == 's' || *format == 'p'
		|| *format == 'd' || *format == 'i' || *format == 'u'
		|| *format == 'x' || *format == 'X' || *format == '%')
		return (1);
	return (0);
}

int	is_a_valid_flag(const char *format)
{
	if (*format == '#')
	{
		while (*format == '#')
			format++;
		if (*format == 'x' || *format == 'X')
			return (1);
		return (0);
	}
	if (*format == ' ' || *format == '+')
	{
		while (*format == '+' || *format == ' ')
			format++;
		if (*format == 'd' || *format == 'i' || *format == 's')
			return (1);
		return (0);
	}
	return (0);
}
