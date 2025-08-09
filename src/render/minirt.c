/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:08:16 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/09 13:46:43 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	calculate_color(t_ray *ray, t_scene *scene, int depth)
{
	t_color			color;
	t_hit_record	rec;
	t_ray			reflected_ray;
	t_vector		reflection_dir;

	if (hit_object(ray, scene, &rec) == true)
	{
		if (rec.mat_type == REFLECTIVE && depth > 0)
		{
			reflection_dir = vec_reflect(ray->dir, rec.normal);
			reflected_ray.origin = rec.point;
			reflected_ray.dir = reflection_dir;
			color = calculate_color(&reflected_ray, scene, depth - 1);
		}
		else
			color = rec.color;
		color = color_scale(color_mult(rec.color, scene->ambient.color),
				scene->ambient.brightness);
		color = combine_lighting(color, scene, rec, ray);
	}
	else
		color = starry_sky_color(ray);
	return (color_clamp(color));
}

void	minirt(t_minirt *mrt)
{
	int			x;
	int			y;
	t_ray		ray;
	t_color		color_tmp;
	uint32_t	color;

	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			init_ray(&ray, mrt->scene, x, y);
			color_tmp = calculate_color(&ray, mrt->scene, 5);
			color = combine_color(color_tmp);
			mlx_put_pixel(mrt->img, x, y, color);
			x++;
		}
		y++;
	}
}
