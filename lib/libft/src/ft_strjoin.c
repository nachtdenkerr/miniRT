/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.heilbronn>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:08:37 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/15 19:59:53 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	finallen;
	char	*result;

	finallen = ft_strlen(s1) + ft_strlen(s2) + 1;
	result = (char *)ft_calloc(finallen, sizeof(char));
	if (!result)
		return (free(s1), free(s2), NULL);
	ft_strlcpy(result, s1, ft_strlen(s1) + 1);
	ft_strlcat(result, s2, finallen);
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (result);
}
