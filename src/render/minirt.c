/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:08:16 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/05 16:33:29 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	calculate_color(t_ray *ray, t_scene *scene)
{
	t_color			color;
	t_hit_record	rec;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	if (hit_object(ray, scene, &rec) == true)
	{
		color = rec.color;
	}
	// color = ambient_lighting(color, scene);
	// color = diffuse_lighting(color, ray, scene);
	// color = specular_lighting(color, ray, scene);
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
			// color_tmp = calculate_color(&ray, mrt->scene);
			// color = combine_color(color_tmp);
			// mlx_put_pixel(mrt->img, x, y, color);
		}
		x++;
	}
	y++;
}
