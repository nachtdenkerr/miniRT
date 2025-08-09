/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_wrapper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:40:20 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/09 14:23:38 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	hit_plane_wrapper(void *data, t_ray *ray, t_hit_record *rec, t_mat mat)
{
	bool		hit;
	t_texture	checker;

	hit = hit_plane(((t_plane *)data), ray, rec);
	if (hit == false)
		return (false);
	if (mat == CHECKER)
	{
		checker_texture_init(&checker, 5.0, 5.0);
		get_plane_uv(rec, ((t_plane *)data)->point);
		rec->color = checker_texture(checker, rec->u, rec->v);
	}
	return (hit_plane(((t_plane *)data), ray, rec));
}

bool	hit_sphere_wrapper(void *data, t_ray *ray, t_hit_record *rec, t_mat mat)
{
	bool		hit;
	t_texture	checker;

	hit = hit_sphere(((t_sphere *)data), ray, rec);
	if (hit == false)
		return (false);
	if (mat == CHECKER)
	{
		get_sphere_uv(rec, ((t_sphere *)data)->center,
			((t_sphere *)data)->radius);
		checker_texture_init(&checker, 30.0, 20.0);
		rec->color = checker_texture(checker, rec->u, rec->v);
	}
	return (hit_sphere(((t_sphere *)data), ray, rec));
}

bool	hit_cylinder_wrapper(void *data, t_ray *ray,
			t_hit_record *rec, t_mat mat)
{
	mat = NORMAL;
	if (mat == CHECKER)
	{
	}
	return (hit_cylinder(((t_cylinder *)data), ray, rec));
}

bool	hit_cone_wrapper(void *data, t_ray *ray, t_hit_record *rec, t_mat mat)
{
	mat = NORMAL;
	if (mat == CHECKER)
	{
	}
	return (hit_cone(((t_cone *)data), ray, rec));
}

// Loop through all objects in the scene and check if the ray hits any of them
// If it does, update the hit record with the closest hit
// Return true if any object was hit, false otherwise
bool	hit_object(t_ray *ray, t_scene *scene, t_hit_record *rec)
{
	int				i;
	bool			hit;
	double			closest_t;
	t_object		*obj;
	t_hit_record	tmp_rec;

	i = 0;
	hit = false;
	closest_t = INFINITY;
	while (i < scene->obj_capacity)
	{
		obj = &scene->objects[i];
		if (obj->hit(obj->data, ray, &tmp_rec, obj->mat))
		{
			if (tmp_rec.t > 0 && tmp_rec.t < closest_t)
			{
				closest_t = tmp_rec.t;
				*rec = tmp_rec;
				rec->mat = obj->mat;
				hit = true;
			}
		}
		i++;
	}
	return (hit);
}
