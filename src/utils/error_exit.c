/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:36:24 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/13 15:59:45 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// Print error and exit. !!!needs to be to stderr
void	error_exit(const char *msg)
{
	printf("Error\n%s\n", msg);
	exit(EXIT_FAILURE);
}

void	malloc_failure_exit(void)
{
	ft_putstr_fd("Failed Malloc\n", 2);
	exit (1);
}

void	malloc_failure_obj_creation_exit(t_scene *scene, char **tokens)
{
	ft_putstr_fd("Failed Malloc\n", 2);
	free_arr(tokens);
	cleanup_scene(scene);
	exit (1);
}

u_int32_t	combine_color(t_color a)
{
	u_int32_t	c;

	c = (a.r << 24) | (a.g << 16) | (a.b << 8) | 0xFF;
	return (c);
}
