/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:08:16 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/06 19:53:54 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	calculate_color(t_ray *ray, t_scene *scene)
{
	t_color			color;
	t_hit_record	rec;
	t_light			*light;
	int				light_index;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	light_index = 0;
	while (light_index < scene->light_count)
	{
		light = &scene->lights[light_index];
		if (hit_object(ray, scene, &rec) == true)
		{
			color = color_scale(rec.color, scene->ambient.brightness);
			color = diffuse_lighting(color, light, &rec);
			color = specular_lighting(color, ray, light, &rec);
		}
		light_index++;
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
