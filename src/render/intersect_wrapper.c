/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_wrapper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:40:20 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/05 10:42:31 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	hit_plane_wrapper(void *data, t_ray *ray, double *t)
{
	return (hit_plane(((t_plane *)data), ray, t));
}

bool	hit_sphere_wrapper(void *data, t_ray *ray, double *t)
{
	return (hit_sphere(((t_sphere *)data), ray, t));
}

bool	hit_cylinder_wrapper(void *data, t_ray *ray, double *t)
{
	return (hit_cylinder(((t_cylinder *)data), ray, t));
}

bool	hit_cone_wrapper(void *data, t_ray *ray, double *t)
{
	return (hit_cone(((t_cone *)data), ray, t));
}

bool	hit_object(t_ray *ray, t_scene *scene, double *t, t_object **hit_obj)
{
	double		t_tmp;
	double		closest_t;
	bool		hit;
	t_object	*obj;
	int			i;

	hit = false;
	i = 0;
	closest_t = INFINITY;
	while (i < scene->obj_capacity)
	{
		obj = &scene->objects[i];
		if (obj->hit(obj->data, ray, &t_tmp))
		{
			if (t_tmp > EPSILON && t_tmp < closest_t)
			{
				closest_t = t_tmp;
				*hit_obj = obj;
				hit = true;
			}
		}
		i++;
	}
	if (hit == true)
		*t = closest_t;
	return (false);
}
