/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 12:47:52 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/08 13:16:28 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, int n)
{
	char	*dup;
	int		c;
	int		d;

	c = 0;
	d = 0;
	if (!src)
		return (NULL);
	dup = (char *)ft_calloc(n + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	while (src[d] != '\0' && c < n)
	{
		dup[c] = src[d];
		c++;
		d++;
	}
	dup[c] = '\0';
	return (dup);
}

char	*ft_strdup(const char *src)
{
	char	*dup;
	int		c;

	c = 0;
	while (src[c] != '\0')
		c++;
	c++;
	dup = (char *)ft_calloc(c, sizeof(char));
	if (dup == NULL)
		return (NULL);
	c = 0;
	while (src[c] != '\0')
	{
		dup[c] = src[c];
		c++;
	}
	dup[c] = src[c];
	return (dup);
}
