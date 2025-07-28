/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:36:24 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/28 11:47:18 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// Print error and exit.
void	error_exit(const char *msg)
{
	printf("Error\n%s\n", msg);
	exit(EXIT_FAILURE);
}

