/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:55:54 by jmutschl          #+#    #+#             */
/*   Updated: 2025/07/29 19:27:58 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	reset_index(t_scene *scene)
{
	scene->l_index = 0;
	scene->sp_index = 0;
	scene->pl_index = 0;
	scene->cy_index = 0;
	scene->co_index = 0;
}

void	init_element_counts(t_scene *scene)
{
	scene->ambiant_count = 0;
	scene->camera_count = 0;
	scene->light_count = 0;
	scene->sphere_count = 0;
	scene->plane_count = 0;
	scene->cylinder_count = 0;
	scene->cone_count = 0;
	scene->l_index = 0;
	scene->sp_index = 0;
	scene->pl_index = 0;
	scene->cy_index = 0;
	scene->co_index = 0;
}

static void	init_element_arrays_pl_cy(t_scene *scene)
{
	if (scene->plane_count != 0)
	{
		scene->planes = malloc(scene->plane_count * sizeof(t_plane));
		if (!scene->planes)
		{
			free(scene->lights);
			free(scene->spheres);
			malloc_failure_exit();
		}
	}
	else
		scene->planes = NULL;
	if (scene->cylinder_count != 0)
	{
		scene->cylinders = malloc(scene->cylinder_count * sizeof(t_cylinder));
		if (!scene->cylinders)
		{
			free(scene->lights);
			free(scene->spheres);
			free(scene->planes);
			malloc_failure_exit();
		}
	}
	else
		scene->cylinders = NULL;
}

static void	init_element_arrays_cone(t_scene *scene)
{
	if (scene->cone_count != 0)
	{
		scene->cones = malloc(scene->cone_count * sizeof(t_cone));
		if (!scene->cones)
		{
			free(scene->lights);
			free(scene->spheres);
			free(scene->planes);
			free(scene->cylinders);
			malloc_failure_exit();
		}
	}
	else
		scene->cones = NULL;
}

void	init_element_arrays(t_scene *scene)
{
	scene->lights = malloc(scene->light_count * sizeof(t_light));
	if (!scene->lights)
		malloc_failure_exit();
	if (scene->sphere_count != 0)
	{
		scene->spheres = malloc(scene->sphere_count * sizeof(t_sphere));
		if (!scene->spheres)
		{
			free(scene->lights);
			malloc_failure_exit();
		}
	}
	else
		scene->spheres = NULL;
	init_element_arrays_pl_cy(scene);
	init_element_arrays_cone(scene);
}
