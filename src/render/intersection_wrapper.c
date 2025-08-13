/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_wrapper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:40:20 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/13 15:56:31 by thudinh          ###   ########.fr       */
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
	t_cylinder	*cy;

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
	t_triangle	*tri;

	tri = (t_triangle *)data;
	if (!hit_triangle(tri, ray, rec))
		return (false);
	rec->mat = tri->mat;
	rec->mat_val = tri->mat_value;
	return (true);
}
