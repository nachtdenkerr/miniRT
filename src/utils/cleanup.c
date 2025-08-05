/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:44 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/05 10:57:17 by thudinh          ###   ########.fr       */
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
	if (scene->lights)
		free(scene->lights);
	if (scene->objects)
		free(scene->objects);
	// if (scene->planes)
	// 	free(scene->planes);
	// if (scene->cylinders)
	// 	free(scene->cylinders);
	// if (scene->cones)
	// 	free(scene->cones);
}
