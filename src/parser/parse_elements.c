/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:09:39 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/05 09:41:21 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_vector	parse_vector(char *str, char **tokens, t_scene *scene)
{
	t_vector	vec;
	char		**arr;
	int			flag;

	flag = 0;
	arr = ft_split(str, ',');
	if (!arr)
		free_and_failed_malloc(tokens, scene);
	if (!arr[0] || !arr[1] || !arr[2] || arr[3])
		invalid_argc_exit(tokens, arr, scene, 1);
	vec.x = ft_atof(arr[0], &flag, 1, 0);
	if (flag)
		invalid_vector_val_exit(arr[0], tokens, arr, scene);
	vec.y = ft_atof(arr[1], &flag, 1, 0);
	if (flag)
		invalid_vector_val_exit(arr[1], tokens, arr, scene);
	vec.z = ft_atof(arr[2], &flag, 1, 0);
	if (flag)
		invalid_vector_val_exit(arr[2], tokens, arr, scene);
	free_arr(arr);
	return (vec);
}

t_color	parse_color(char *str, char **tokens, t_scene *scene)
{
	t_color		c;
	char		**arr;
	int			flag;

	flag = 0;
	arr = ft_split(str, ',');
	if (!arr)
		free_and_failed_malloc(tokens, scene);
	if (!arr[0] || !arr[1] || !arr[2] || arr[3])
		invalid_argc_exit(tokens, arr, scene, 1);
	c.r = ft_atoi_color(arr[0], &flag);
	if (flag)
		invalid_color_val_exit(arr[0], tokens, arr, scene);
	c.g = ft_atoi_color(arr[1], &flag);
	if (flag)
		invalid_color_val_exit(arr[1], tokens, arr, scene);
	c.b = ft_atoi_color(arr[2], &flag);
	if (flag)
		invalid_color_val_exit(arr[2], tokens, arr, scene);
	free_arr(arr);
	return (c);
}

void	parse_ambient(char **tokens, t_scene *scene)
{
	t_ambient	a;
	int			flag;

	flag = 0;
	if (!tokens[1] || !tokens[2] || tokens[3])
		invalid_argc_exit(tokens, NULL, scene, 7);
	a.brightness = ft_atof(tokens[1], &flag, 1, 0);
	if (flag || a.brightness < 0.0 || a.brightness > 1.0)
		invalid_arg_exit(tokens, scene, 9);
	a.color = parse_color(tokens[2], tokens, scene);
	scene->ambient = a;
}

void	parse_light(char **tokens, t_scene *scene)
{
	t_light	l;
	int		flag;

	flag = 0;
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		invalid_argc_exit(tokens, NULL, scene, 6);
	l.position = parse_vector(tokens[1], tokens, scene);
	l.brightness = ft_atof(tokens[2], &flag, 1, 0);
	if (flag || l.brightness < 0.0 || l.brightness > 1.0)
		invalid_arg_exit(tokens, scene, 8);
	l.color = parse_color(tokens[3], tokens, scene);
	scene->lights[scene->l_index] = l;
	scene->l_index++;
}

void	parse_camera(char **tokens, t_scene *scene)
{
	t_camera	c;
	int			flag;

	flag = 0;
	if (!tokens[1] || !tokens[2] || !tokens[3] || tokens[4])
		invalid_argc_exit(tokens, NULL, scene, 8);
	c.position = parse_vector(tokens[1], tokens, scene);
	c.orientation = parse_vector(tokens[2], tokens, scene);
	if (check_if_unit_vector(c.orientation))
		invalid_arg_exit(tokens, scene, 10);
	c.fov = ft_atof(tokens[3], &flag, 1, 0);
	if (flag || c.fov < 0.0 || c.fov > 180.0)
		invalid_arg_exit(tokens, scene, 11);
	scene->camera = c;
}
