/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:48:09 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/29 20:30:48 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	check_set(char const s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == s1)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	begining;
	size_t	end;

	begining = 0;
	if (!s1 || s1[0] == '\0' || (s1[0] == set[0] && s1[1] == '\0'))
		return (ft_strdup(""));
	end = ft_strlen(s1);
	if (!set)
		return (ft_strdup(s1));
	while (check_set(s1[begining], set))
		begining++;
	while (check_set(s1[end - 1], set))
		end--;
	return (ft_substr(s1, begining, end - begining));
}
