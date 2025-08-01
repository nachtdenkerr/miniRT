/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 11:40:29 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/29 11:40:33 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

size_t	ft_strlen_gnl(const char *s)
{
	int	len;

	len = 0;
	if (!s || *s == '\0')
		return (0);
	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}

void	*ft_memmove_gnl(void *dst, const void *src, size_t len)
{
	unsigned char		*cdst;
	unsigned char const	*csrc;

	if (!dst && !src)
		return (NULL);
	if (len == 0)
		return (dst);
	cdst = (unsigned char *) dst;
	csrc = (unsigned const char *) src;
	if (cdst > csrc && cdst < csrc + len)
	{
		cdst += len - 1;
		csrc += len - 1;
		while (len--)
			*cdst-- = *csrc--;
	}
	else
	{
		while (len--)
			*cdst++ = *csrc++;
	}
	return (dst);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	int		len_s1;
	int		len_s2;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen_gnl(s1);
	len_s2 = ft_strlen_gnl(s2);
	res = malloc ((len_s1 + len_s2 + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	res[0] = '\0';
	ft_memmove_gnl(res, s1, len_s1);
	ft_memmove_gnl(res + len_s1, s2, len_s2);
	res[len_s1 + len_s2] = '\0';
	return (res);
}

char	*ft_strchr_gnl(const char *s, int c)
{
	char	cc;

	if (!s)
		return (NULL);
	cc = (char)c;
	while (*s != '\0')
	{
		if (*s == cc)
			return ((char *)s);
		s++;
	}
	if (cc == '\0')
		return ((char *)s);
	return (NULL);
}
