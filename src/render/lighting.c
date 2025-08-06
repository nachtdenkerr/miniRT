/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:17:25 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/06 17:54:20 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

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
	specular_intensity = fmax(vec_dot(vec_scale(reflect_dir, -1.0), view_dir), 0.0);
	specular_color = color_scale(color, specular_intensity * light->brightness);
	return (color_add(color, specular_color));
}
