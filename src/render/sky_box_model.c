/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_box_model.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 12:55:00 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/09 13:13:34 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

unsigned int	hash_direction(t_vector dir)
{
	unsigned int	hash;
	int				x;
	int				y;
	int				z;

	x = (int)(floor(dir.x * 1000));
	y = (int)(floor(dir.y * 1000));
	z = (int)(floor(dir.z * 1000));
	hash = (unsigned int)(x * 73856093 ^ y * 19349663 ^ z * 83492791);
	return (hash);
}

t_color	starry_sky_color(t_ray *ray)
{
	unsigned int	hash;
	t_vector		dir;
	double			noise;

	dir = vec_normalize(ray->dir);
	hash = hash_direction(dir);
	noise = (hash % 10000) / 10000.0;
	if (noise < 0.999)
		return (create_color(0, 0, 0));
	else
		return (create_color(255, 255, 255));
}
