/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_wrapper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:40:20 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/05 15:55:31 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	hit_plane_wrapper(void *data, t_ray *ray, t_hit_record *rec)
{
	return (hit_plane(((t_plane *)data), ray, rec));
}

bool	hit_sphere_wrapper(void *data, t_ray *ray, t_hit_record *rec)
{
	return (hit_sphere(((t_sphere *)data), ray, rec));
}

bool	hit_cylinder_wrapper(void *data, t_ray *ray, t_hit_record *rec)
{
	return (hit_cylinder(((t_cylinder *)data), ray, rec));
}

bool	hit_cone_wrapper(void *data, t_ray *ray, t_hit_record *rec)
{
	return (hit_cone(((t_cone *)data), ray, rec));
}

bool	hit_object(t_ray *ray, t_scene *scene, t_hit_record *rec)
{
	t_hit_record	tmp_rec;
	double			closest_t;
	bool			hit;
	t_object		*obj;
	int				i;

	hit = false;
	i = 0;
	closest_t = INFINITY;
	while (i < scene->obj_capacity)
	{
		obj = &scene->objects[i];
		if (obj->hit(obj->data, ray, &tmp_rec))
		{
			if (tmp_rec.t > 0 && tmp_rec.t < closest_t)
			{
				closest_t = tmp_rec.t;
				rec = &tmp_rec;
				hit = true;
			}
		}
		i++;
	}
	return (hit);
}
