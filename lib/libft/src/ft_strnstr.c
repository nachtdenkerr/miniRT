/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 21:14:46 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/08 13:16:36 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	c;
	size_t	d;

	c = 0;
	d = 0;
	if (!*needle)
		return ((char *)haystack);
	while (haystack[c] != '\0' && c < len)
	{
		d = 0;
		if (haystack[c] == needle[d])
		{
			while (haystack[c + d] == needle[d] && needle[d] != '\0'
				&& (c + d) < len)
				d++;
		}
		if (needle[d] == '\0')
			return ((char *)&haystack[c]);
		c++;
	}
	return (NULL);
}
