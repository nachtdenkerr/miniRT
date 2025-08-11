/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:36:24 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/11 10:31:31 by jmutschl         ###   ########.fr       */
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
