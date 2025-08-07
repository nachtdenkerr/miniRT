/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:08:16 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/07 21:03:59 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	is_in_shadow(t_scene *scene, t_light *light, t_ray *shadow)
{
	t_hit_record	empty_rec;
	double			distance_to_light;

	if (hit_object(shadow, scene, &empty_rec) == true)
	{
		distance_to_light = vec_length(vec_sub(light->position,
					shadow->origin));
		if (empty_rec.t < distance_to_light)
			return (true);
	}
	return (false);
}

t_color	calculate_color(t_ray *ray, t_scene *scene)
{
	t_color			color;
	t_hit_record	rec;
	t_light			*light;
	int				light_index;
	t_ray			shadow_ray;

	color = create_color(0, 0, 0);
	if (hit_object(ray, scene, &rec) == true)
	{
		color = color_scale(rec.color, scene->ambient.brightness);
		light_index = -1;
		while (++light_index < scene->light_count)
		{
			light = &scene->lights[light_index];
			shadow_ray.origin = vec_add(rec.point, vec_scale(rec.normal, EPSILON));
			shadow_ray.dir = vec_normalize(vec_sub(light->position, rec.point));
			if (is_in_shadow(scene, light, &shadow_ray) == true)
				continue ;
			color = color_add(color, diffuse_lighting(rec.color, light, &rec));
			color = specular_lighting(color, ray, light, &rec);
		}
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
			color_tmp = calculate_color(&ray, mrt->scene);
			color = combine_color(color_tmp);
			mlx_put_pixel(mrt->img, x, y, color);
			x++;
		}
		y++;
	}
}
