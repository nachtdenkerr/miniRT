/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aiia.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:08:59 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/02 12:06:11 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_len(int n)
{
	long	number;
	int		count;

	number = n;
	count = 0;
	if (number < 0)
	{
		count++;
		number = number * -1;
	}
	while (number >= 10)
	{
		count++;
		number = number / 10;
	}
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;
	long	number;

	len = n_len(n);
	result = (char *)ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	number = n;
	if (number < 0)
	{
		result[0] = '-';
		number = number * -1;
	}
	len--;
	while (number >= 10)
	{
		result[len] = (number % 10) + 48;
		number = number / 10;
		len--;
	}
	result[len] = number + 48;
	return (result);
}

static int	minusplus(const char *str, int *c)
{
	int	c1;
	int	result;

	c1 = 0;
	result = 1;
	while ((str[c1] >= 9 && str[c1] <= 13) || str[c1] == 32)
		c1++;
	if (str[c1] == 43 || str[c1] == 45)
	{
		if (str[c1] == 45)
			result = result * -1;
		c1++;
	}
	*c = c1;
	return (result);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	c;
	int	mp;

	result = 0;
	mp = minusplus(str, &c);
	while (str[c] != '\0' && str[c] >= '0' && str[c] <= '9')
	{
		result = result * 10;
		result = result + str[c] - 48;
		c++;
	}
	result = result * mp;
	return (result);
}
