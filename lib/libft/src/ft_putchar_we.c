/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_we.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:35:51 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/02 10:42:01 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_we(char c, int *num_char, int *error)
{
	*error = write(1, &c, 1);
	if (*error == -1)
		return ;
	*num_char += 1;
}

void	ft_putstr_we(char *s, int *num_char, int *error)
{
	int	s_len;

	s_len = ft_strlen(s);
	*error = write(1, s, s_len);
	*num_char += s_len;
}

void	ft_putsign_we(int *n, int *num_char, int *error, int *flag)
{
	if (*n < 0)
	{
		ft_putchar_we('-', num_char, error);
		*n *= -1;
	}
	else if (*n >= 0 && *flag == 1)
		ft_putchar_we('+', num_char, error);
	else if (*n >= 0 && *flag == 2)
		ft_putchar_we(' ', num_char, error);
	*flag = 0;
}

void	ft_putnbr_we(int n, int *num_char, int *error, int flag)
{
	if (n == -2147483648)
	{
		ft_putstr_we("-2147483648", num_char, error);
		return ;
	}
	ft_putsign_we (&n, num_char, error, &flag);
	if (*error == -1)
		return ;
	if (n < 10 && *error != -1)
	{
		ft_putchar_we(n + '0', num_char, error);
		return ;
	}
	else if (n >= 10 && *error != -1)
	{
		ft_putnbr_we(n / 10, num_char, error, flag);
		if (*error == -1)
			return ;
	}
	if (*error != -1)
		ft_putchar_we((n % 10) + '0', num_char, error);
	return ;
}
