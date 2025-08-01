/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:52:17 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/08 13:15:34 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	ch;

	ch = (char)c;
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == ch)
			return ((char *)s);
		s++;
	}
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	char		ch;
	const char	*temp;

	temp = NULL;
	ch = (char)c;
	while (*s != '\0')
	{
		if (*s == ch)
			temp = s;
		s++;
	}
	if (ch == '\0')
		return ((char *)s);
	return ((char *)temp);
}
