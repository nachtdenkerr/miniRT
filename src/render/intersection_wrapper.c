/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_wrapper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:40:20 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/12 15:37:56 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	hit_plane_wrapper(void *data, t_ray *ray, t_hit_record *rec)
{
	bool		hit;
	t_texture	checker;
	t_plane		*pl;
	
	pl = (t_plane *)data;
	hit = hit_plane(pl, ray, rec);
	if (hit == false)
		return (false);
	rec->mat = pl->mat;
	rec->mat_val = pl->mat_value;
	if (pl->mat == CHECKER)
	{
		checker_texture_init(&checker, 1.0, 1.0, pl->mat_value);
		get_plane_uv(rec, pl->point);
		rec->color = checker_texture(checker, rec->u, rec->v);
	}
	return (true);
}

bool	hit_sphere_wrapper(void *data, t_ray *ray, t_hit_record *rec)
{
	bool		hit;
	t_texture	checker;
	t_sphere	*sp;

	sp = (t_sphere *)data;
	hit = hit_sphere(sp, ray, rec);
	if (hit == false)
		return (false);
	rec->mat = sp->mat;
	rec->mat_val = sp->mat_value;
	if (sp->mat == CHECKER)
	{
		get_sphere_uv(rec, sp->center, sp->radius);
		checker_texture_init(&checker, 15.0, 10.0, sp->mat_value);
		rec->color = checker_texture(checker, rec->u, rec->v);
	}
	return (true);
}

bool	hit_cylinder_wrapper(void *data, t_ray *ray,
			t_hit_record *rec)
{
	t_cylinder *cy;

	cy = (t_cylinder *)data;
	if (!hit_cylinder(cy, ray, rec))
		return (false);
	rec->mat = cy->mat;
	rec->mat_val = cy->mat_value;
	return (true);
}

bool	hit_cone_wrapper(void *data, t_ray *ray, t_hit_record *rec)
{
	t_cone	*co;

	co = (t_cone *)data;
	if (!hit_cone(co, ray, rec))
		return (false);	
	rec->mat = co->mat;
	rec->mat_val = co->mat_value;
	return (true);
}

bool	hit_triangle_wrapper(void *data, t_ray *ray, t_hit_record *rec)
{
	t_triangle *tri;

	tri = (t_triangle *)data;
	if (!hit_triangle(tri, ray, rec))
		return (false);
	rec->mat = tri->mat;
	rec->mat_val = tri->mat_value;
	return (true);
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
		if (obj->hit(obj->data, ray, &tmp_rec))
		{
			if (tmp_rec.t > 0 && tmp_rec.t < closest_t)
			{
				closest_t = tmp_rec.t;
				*rec = tmp_rec;
				hit = true;
			}
		}
		i++;
	}
	return (hit);
}
