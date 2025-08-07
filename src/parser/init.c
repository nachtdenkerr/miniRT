/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:55:54 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/07 11:40:00 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	reset_index(t_scene *scene)
{
	scene->l_index = 0;
}

void	init_element_counts(t_scene *scene)
{
	scene->ambiant_count = 0;
	scene->camera_count = 0;
	scene->light_count = 0;
	scene->l_index = 0;
	scene->obj_index = 0;
	scene->obj_capacity = 0;
}

void	init_element_arrays(t_scene *scene)
{
	scene->lights = malloc(scene->light_count * sizeof(t_light));
	if (!scene->lights)
		malloc_failure_exit();
	if (scene->obj_capacity != 0)
	{
		scene->objects = malloc(scene->obj_capacity * sizeof(t_object));
		if (!scene->objects)
		{
			free(scene->lights);
			malloc_failure_exit();
		}
	}
}
