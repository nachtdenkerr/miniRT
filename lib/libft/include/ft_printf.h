/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:48:04 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/08 12:16:20 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include "libft.h"

int		is_a_conversion(const char *format);
int		is_a_valid_flag(const char *format);

void	ft_putchar_we(char c, int *num_char, int *error);
void	ft_putstr_we(char *s, int *num_char, int *error);
void	ft_putnbr_we(int n, int *num_char, int *error, int flag_sign);

void	print_hex_lower(unsigned int num, int *num_char,
			int *error, int flag);
void	print_hex_upper(unsigned int num, int *num_char,
			int *error, int flag);
void	print_ptr(unsigned long long add, int *num_char, int *error);
void	print_unsigned_int(unsigned int num, int *num_char, int *error);

void	print_conversion(const char *format, va_list *ap,
			int *num_char, int *error);
void	print_with_format(const char *format, va_list *ap,
			int *num_char, int *error);
void	print_hex_flag(const char *format, va_list *ap,
			int *num_char, int *error);
void	print_space_sign_flag(const char *format, va_list *ap,
			int *num_char, int *error);
void	print_with_flag(const char *format, va_list *ap,
			int *num_char, int *error);
int		ft_printf(const char *format, ...);
#endif
