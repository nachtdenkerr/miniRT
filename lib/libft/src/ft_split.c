/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:47:28 by jmutschl          #+#    #+#             */
/*   Updated: 2025/06/11 14:27:51 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	quote_check(char c)
{
	return (c == '\'' || c == '\"');
}

static int	skip_quote(const char *s, int i, char quote)
{
	while (s[i])
	{
		if (s[i] == quote && s[i - 1] != '\\')
			break ;
		i++;
	}
	if (s[i] == quote)
		i++;
	return (i);
}

static int	count_words(const char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c || (i == 0 && quote_check(s[i])))
			i++;
		if (!s[i])
			break ;
		count++;
		if (quote_check(s[i]) && s[i - 1] != '\\')
			i = skip_quote(s, i + 1, s[i]);
		else
		{
			while (s[i] && s[i] != c && (!quote_check(s[i])
					|| (i != 0 && s[i - 1] == '\\')))
				i++;
		}
	}
	return (count);
}

static int	create_word(char **result, const char *s, int *i, char c)
{
	int		start;
	char	q;

	while (s[*i] == c)
		(*i)++;
	if (!s[*i])
		return (0);
	start = *i;
	if (quote_check(s[*i]))
	{
		q = s[(*i)++];
		start = *i;
		*i = skip_quote(s, *i, q);
		result[0] = ft_strndup(s + start, *i - start - 1);
	}
	else
	{
		while (s[*i] && s[*i] != c && (!quote_check(s[*i])
				|| (*i != 0 && s[*i - 1] == '\\')))
			(*i)++;
		result[0] = ft_strndup(s + start, *i - start);
	}
	if (!result[0])
		return (-1);
	return (1);
}

char	**ft_split(const char *s, char c)
{
	char	**result;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	while (j < count)
	{
		if (!create_word(&result[j], s, &i, c))
		{
			while (j-- > 0)
				free((void *)result[j]);
			return (free(result), NULL);
		}
		j++;
	}
	result[j] = NULL;
	return (result);
}

//#include <stdio.h>
//#include <stdlib.h>

////char    **ft_split(char const *s, char c); 

//int main(void)
//{
//    char **result;
//    char *str = "awk '{count++} END {print count}'";
//    char delimiter = ' ';
//    int i = 0;
//	printf("%i\n", count_words(str, delimiter, 0 ,0));

//    // Call ft_split
//    result = ft_split(str, delimiter);
//    if (!result)
//    {
//        printf("Memory allocation failed or NULL returned.\n");
//        return (1);
//    }

//    // Print each split string
//    printf("Split result:\n");
//    while (result[i])
//    {
//        printf("result[%d]: \"%s\"\n", i, result[i]);
//        free(result[i]); // Free each allocated string
//        i++;
//    }

//    free(result); // Free the array itself
//    return (0);
//}
