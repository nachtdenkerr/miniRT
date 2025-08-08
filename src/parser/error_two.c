/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:26:22 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/07 14:52:32 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
 
void	not_valid_format_exit(char **tokens, t_scene *scene, int x)
{
	free_arr(tokens);
	cleanup_scene(scene);
	if (x == 0)
		ft_putstr_fd("Invalid Vector or Point Format\n", 2);
	if (x == 1)
		ft_putstr_fd("Invalid Color Format\n", 2);
	exit(1);
}

void	invalid_argc_exit(char **tokens, char **arr, t_scene *scene, int x)
{
	free_arr(tokens);
	if (arr)
		free_arr(arr);
	cleanup_scene(scene);
	if (x == 1)
		ft_putstr_fd("Invalid vector or color format expected 3\n", 2);
	else if (x == 2)
		ft_putstr_fd("Invalid number of arguments for sphere expected 4\n", 2);
	else if (x == 3)
		ft_putstr_fd("Invalid number of arguments for plane expected 4\n", 2);
	else if (x == 4)
		ft_putstr_fd("Invalid number of argument for cylinder expected 6\n", 2);
	else if (x == 5)
		ft_putstr_fd("Invalid number of arguments for cone expected 5\n", 2);
	else if (x == 6)
		ft_putstr_fd("Invalid number of arguments for light expected 4\n", 2);
	else if (x == 7)
		ft_putstr_fd("Invalid number of arguments for ambient expected 3\n", 2);
	else if (x == 8)
		ft_putstr_fd("Invalid number of arguments for camera expected 4\n", 2);
	exit (1);
}

void	invalid_vector_val_exit(char *str, char **tokens,
			char **arr, t_scene *scene)
{
	ft_putstr_fd("Invalid vector value: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	free_arr(tokens);
	free_arr(arr);
	cleanup_scene(scene);
	exit (1);
}

void	invalid_color_val_exit(char *str, char **tokens,
			char **arr, t_scene *scene)
{
	ft_putstr_fd("Invalid color value: ", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	free_arr(tokens);
	free_arr(arr);
	cleanup_scene(scene);
	exit (1);
}

void	invalid_arg_exit(char **tokens, t_scene *scene, int x)
{
	free_arr(tokens);
	cleanup_scene(scene);
	if (x == 1)
		ft_putstr_fd("Invalid diameter for sphere\n", 2);
	else if (x == 2)
		ft_putstr_fd("Invalid normalized vector for plane\n", 2);
	else if (x == 3)
		ft_putstr_fd("Invalid normalized vector for cylinder axis\n", 2);
	else if (x == 4)
		ft_putstr_fd("Invalid diameter for cylinder\n", 2);
	else if (x == 5)
		ft_putstr_fd("Invalid height for cylinder\n", 2);
	else if (x == 6)
		ft_putstr_fd("Invalid normalized vector for cone axis\n", 2);
	else if (x == 7)
		ft_putstr_fd("Invalid angle for cone\n", 2);
	else if (x == 8)
		ft_putstr_fd("Invalid brightness ratio for Light\n", 2);
	else if (x == 9)
		ft_putstr_fd("Invalid brightness ratio for ambient\n", 2);
	else if (x == 10)
		ft_putstr_fd("Invalid normalized vector for camera\n", 2);
	else if (x == 11)
		ft_putstr_fd("Invalid fov for camera\n", 2);
	exit(1);
}
