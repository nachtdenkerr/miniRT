/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:08:16 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/04 16:37:43 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	init_ray(t_ray *ray, t_scene *scene, int x, int y)
{
	ray->dir = calc_ray_vector(x, y);
	ray->origin = scene->camera->position;
	ray->hit_point = NULL;
}

t_color	calculate_color(t_ray *ray, t_scene *scene)
{
	t_color	color;

	color = object_hit(ray, scene); //set ray->hit_point here
	color = ambient_lighting(color, scene);
	color = diffuse_lighting(color, ray, scene);
	color = specular_lighting(color, ray, scene);
	return (color);
}

void	minirt(t_minirt *mrt)
{
	int			x;
	int			y;
	t_ray		ray;
	t_color		color_tmp;
	u_int32_t	color;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			init_ray(&ray, mrt->scene, x, y);
			color_tmp = calculate_color(&ray, mrt->scene);
			color = parse_color(color_tmp);
			mlx_put_pixel(mrt->img, x, y, color);
			x++;
		}
		y++;
	}
}
