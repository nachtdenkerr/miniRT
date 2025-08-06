/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:44 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/06 11:41:37 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	cleanup_scene(t_scene *scene)
{
	int i;

	i = 0;
	if (scene->lights)
		free(scene->lights);
	while (i <= scene->obj_index)
	{
		free((scene->objects[i]).data);
		i++;
	}
	if (scene->objects)
		free(scene->objects);
	// if (scene->planes)
	// 	free(scene->planes);
	// if (scene->cylinders)
	// 	free(scene->cylinders);
	// if (scene->cones)
	// 	free(scene->cones);
}
