/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:17:25 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/09 13:27:31 by thudinh          ###   ########.fr       */
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

t_color	diffuse_lighting(t_color color, t_light *light, t_hit_record *rec)
{
	t_vector	light_dir;
	double		intensity;
	t_color		diffuse_color;

	light_dir = vec_normalize(vec_sub(light->position, rec->point));
	intensity = fmax(vec_dot(rec->normal, light_dir), 0.0);
	diffuse_color = color_scale(light->color, intensity * light->brightness);
	return (color_mult(color, diffuse_color));
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

t_color	combine_lighting(t_color color, t_scene *scene,
		t_hit_record rec, t_ray *ray)
{
	int			light_index;
	t_ray		shadow_ray;
	t_light		*light;

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
	return (color);
}
