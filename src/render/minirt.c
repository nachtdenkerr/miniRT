/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:08:16 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/04 15:25:32 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	init_ray(t_ray *ray, int i, int j)
{
	ray->dir = calc_ray_vector(i, j);
	ray->point = scene->camera->position;
	ray->hit_point = NULL;
}

t_color	calculate_color(t_ray *ray, t_scene *scene)
{
	t_color color;

	color = object_hit(ray, scene); //set ray->hit_point here
	color =  ambient_lightning(color, scene);
	color = diffuse_lightning(color, ray, scene);
	color = specular_lightning(color, ray, scene);
	return (color);
}

void	minirt(t_minirt *mrt)
{
	int			i;
	int			j;
	t_ray		ray;
	t_color		color_tmp;
	u_int32_t	color;
	

	i = 0;
	while (i < 800)
	{
		j = 0;
		while (j < 600)
		{
			init_ray(&ray, i, j);
			color_tmp = calculate_color(&ray, mrt->scene);
			color = parse_color(color_tmp)
			mlx_pit_pixel(mrt->img, x, y, color);
			j++;
		}
		i++;
	}
}
