/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/09 14:04:03 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// Solve quadratic equation for sphere intersection
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
	update_hit_record(rec, point_at(ray, rec->t),
		vec_normalize(vec_sub(rec->point, sphere->center)), sphere->color);
	return (true);
}

// Solve plane intersection
// Return false if the ray is parallel to the plane
bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double		denominator;
	t_vector	normal;
	t_point		point;

	normal = plane->normal;
	if (vec_dot(normal, ray->dir) > 0)
		normal = vec_scale(plane->normal, -1.0);
	denominator = vec_dot(ray->dir, normal);
	if (fabs(denominator) < EPSILON)
		return (false);
	rec->t = vec_dot(vec_sub(plane->point, ray->origin), normal) / denominator;
	if (rec->t < EPSILON)
		return (false);
	point = point_at(ray, rec->t);
	update_hit_record(rec, point, normal, plane->color);
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
