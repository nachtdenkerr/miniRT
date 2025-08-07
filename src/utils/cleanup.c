/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:54:44 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/07 10:52:39 by thudinh          ###   ########.fr       */
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
	int	i;

	i = 0;
	if (scene->lights)
		free(scene->lights);
	while (i < scene->obj_index)
	{
		free((scene->objects[i]).data);
		i++;
	}
	if (scene->objects)
		free(scene->objects);
}
