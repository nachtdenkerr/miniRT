/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:06:56 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/06 15:44:02 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	file_open_error_exit(char *filename)
{
	perror(filename);
	exit(1);
}

void	unknown_identifier_exit(char **tokens)
{
	ft_putstr_fd("Unknown Identifier: ", 2);
	if (tokens && tokens[0])
		ft_putstr_fd(tokens[0], 2);
	ft_putstr_fd("\n", 2);
	free_arr(tokens);
	exit(1);
}

void	error_too_many_elements(int x)
{
	if (x == 1)
		ft_putstr_fd("Multiple ambient lighting declarations\n", 2);
	else if (x == 2)
		ft_putstr_fd("Multiple camera declarations\n", 2);
	exit (1);
}

void	missing_element_exit(int x)
{
	if (x == 1)
		ft_putstr_fd("Ambient lighting is missing\n", 2);
	else if (x == 2)
		ft_putstr_fd("Camera is missing\n", 2);
	else if (x == 3)
		ft_putstr_fd("At least one light must be defined\n", 2);
	else if (x == 4)
		ft_putstr_fd("No renderable objects found\n", 2);
	exit (1);
}

void	free_and_failed_malloc(char **tokens, t_scene *scene)
{
	free_arr(tokens);
	cleanup_scene(scene);
	malloc_failure_exit();
}
