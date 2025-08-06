/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/06 16:08:25 by thudinh          ###   ########.fr       */
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
	rec->point = point_at(ray, rec->t);
	rec->normal = vec_normalize(vec_sub(rec->point, sphere->center));
	rec->color = sphere->color;
	return (true);
}

// not yet finished
bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double		denominator;
	t_vector	oc;
	t_vector	normal;

	normal = plane->normal;
	oc = vec_sub(plane->point, ray->origin);
	denominator = vec_dot(ray->dir, normal);
	if (fabs(denominator) < EPSILON)
	{
		rec->t = 0.0;
		return (false);
	}
	if (denominator < 0)
	{
		normal = vec_scale(normal, -1.0);
		denominator = vec_dot(ray->dir, normal);
	}
	rec->t = -vec_dot(oc, normal) / denominator;
	if (rec->t < EPSILON)
		return (false);
	rec->normal = normal;
	rec->point = point_at(ray, rec->t);
	rec->color = plane->color;
	return (true);
}

bool	hit_cone(t_cone *cone, t_ray *ray, t_hit_record *rec)
{
	double		a;
	double		h;
	double		c;
	double		k_sqr;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cone->apex, ray->origin);
	k_sqr = tan(deg_to_rad(cone->angle)) * tan(deg_to_rad(cone->angle));
	a = vec_dot(ray->dir, ray->dir)
		- (1 + k_sqr) * pow(vec_dot(ray->dir, cone->axis), 2);
	h = vec_dot(ray->dir, oc) - (1 + k_sqr) * vec_dot(ray->dir, cone->axis)
		* vec_dot(oc, cone->axis);
	c = vec_dot(oc, oc) - (1 + k_sqr) * pow(vec_dot(oc, cone->axis), 2);
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	rec->t = (h - sqrt(discriminant)) / a;
	rec->color = cone->color;
	return (true);
}
