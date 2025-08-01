/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:08:51 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/02 11:56:32 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	unsigned int	c;
	unsigned int	d;
	size_t			x;
	size_t			y;

	c = 0;
	d = 0;
	x = ft_strlen(dest);
	y = ft_strlen(src);
	if (dstsize < x)
		return (dstsize + y);
	if (!src)
		return (x);
	if (dstsize > 0)
	{
		while (dest[c] != '\0')
			c++;
		while (src[d] != '\0' && c < (dstsize - 1))
			dest[c++] = src[d++];
		dest[c] = '\0';
	}
	return (x + y);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	unsigned int	c;
	size_t			x;

	c = 0;
	x = ft_strlen(src);
	if (dstsize > 0)
	{
		while (c < dstsize -1 && src[c] != '\0')
		{
			dest[c] = src[c];
			c++;
		}
		dest[c] = '\0';
	}
	return (x);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n < 1)
		return (0);
	while (--n && *s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	if (*s1 != '\0' || *s2 != '\0')
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
	}
	if (*s1 != '\0' || *s2 != '\0')
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}
