/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:17:25 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/07 16:03:16 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	diffuse_lighting(t_color color, t_light *light, t_hit_record *rec)
{
	t_vector	light_dir;
	double		intensity;
	t_color		diffuse_color;

	light_dir = vec_normalize(vec_sub(light->position, rec->point));
	intensity = fmax(vec_dot(rec->normal, light_dir), 0.0);
	diffuse_color = color_mult(color, color_scale(light->color, intensity * light->brightness));
	return (color_add(color, diffuse_color));
}

t_color	specular_lighting(t_color color, t_ray *ray,
		t_light *light, t_hit_record *rec)
{
	t_vector	reflect_dir;
	t_vector	view_dir;
	t_vector	light_dir;
	t_color		specular_color;
	double		specular_intensity;

	view_dir = vec_normalize(vec_sub(ray->origin, rec->point));
	light_dir = vec_normalize(vec_sub(light->position, rec->point));
	reflect_dir = vec_reflect(light_dir, rec->normal);
	specular_intensity = pow(fmax(vec_dot(vec_scale(reflect_dir, -1.0),
					view_dir), 0.0), SHINIESS);
	specular_color = color_scale(light->color,
				specular_intensity * light->brightness);
	return (color_add(color, specular_color));
}
