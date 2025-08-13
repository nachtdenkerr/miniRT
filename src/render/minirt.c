/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:08:16 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/13 16:29:22 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	reflect_color(t_ray *ray, t_hit_record *rec, t_scene *scene, int depth)
{
	t_ray			rf_ray;
	t_vector		rf_dir;

	rf_dir = vec_reflect(ray->dir, rec->normal);
	rf_ray.origin = vec_add(rec->point, vec_scale(rf_dir, EPSILON));
	rf_ray.dir = rf_dir;
	return (calculate_color(&rf_ray, scene, depth - 1));
}

t_color	calculate_color(t_ray *ray, t_scene *scene, int depth)
{
	t_color			color;
	t_color			rf_color;
	t_hit_record	rec;

	if (hit_object(ray, scene, &rec) == false)
		return (create_color(0, 0, 0));
	if (depth <= 0)
		return (create_color(0, 0, 0));
	color = color_scale(color_mult(rec.color, scene->ambient.color),
			scene->ambient.brightness);
	color = combine_lighting(color, scene, rec, ray);
	if (rec.mat == REFLECTIVE && depth > 0)
	{
		rf_color = reflect_color(ray, &rec, scene, depth -1);
		color = color_add(color_scale(color, 1.0 - rec.mat_val),
				color_scale(rf_color, rec.mat_val));
	}
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
