/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:29:21 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/08 13:16:44 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	stringlen;
	size_t	finallen;
	char	*result;

	stringlen = ft_strlen(s);
	if (!s || s[0] == '\0')
		return (ft_strdup(""));
	if (stringlen <= (size_t)start)
		return (ft_strdup(""));
	if (len > (stringlen - (size_t)start))
		finallen = (stringlen - (size_t)start + 1);
	else
		finallen = len + 1;
	result = (char *)ft_calloc(finallen, sizeof(char));
	if (!result)
		return (NULL);
	ft_strlcpy(result, s + start, finallen);
	return (result);
}
