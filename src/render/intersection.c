/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/07 10:52:01 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// calculate if rays can hit the sphere
bool	hit_sphere(t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	double		a;
	double		h;
	double		c;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(ray->origin, sphere->center);
	a = vec_dot(ray->dir, ray->dir);
	h = (vec_dot(ray->dir, oc));
	c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = h * h - a * c;
	if (discriminant < 0.0)
		return (false);
	rec->t = (-h - sqrt(discriminant)) / a;
	if (rec->t < EPSILON)
	{
		rec->t = (-h + sqrt(discriminant)) / a;
		if (rec->t < EPSILON)
			return (false);
	}
	// update_hit_record(rec, point_at(ray, rec->t),
	// 		vec_normalize(vec_sub(rec->point, sphere->center)), sphere->color);
	rec->point = point_at(ray, rec->t);
	rec->normal = vec_normalize(vec_sub(rec->point, sphere->center));
	rec->color = sphere->color;
	return (true);
}

// not yet finished
bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double		denominator;
	t_vector	normal;

	normal = plane->normal;
	denominator = vec_dot(ray->dir, normal);
	if (fabs(denominator) < EPSILON)
		return (false);
	rec->t = vec_dot(vec_sub(plane->point, ray->origin), normal) / denominator;
	if (rec->t < EPSILON)
		return (false);
	update_hit_record(rec, point_at(ray, rec->t), normal, plane->color);
	return (true);
}
