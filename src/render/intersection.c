/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/05 13:03:28 by thudinh          ###   ########.fr       */
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

	oc = vec_sub(sphere->center, ray->origin);
	a = vec_dot(ray->dir, ray->dir);
	h = (vec_dot(ray->dir, oc));
	c = vec_dot(oc, oc) - sphere->radius * sphere->radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	rec->t = (h - sqrt(discriminant)) / a;
	if (rec->t < 0)
	{
		rec->t = (h + sqrt(discriminant)) / a;
		if (rec->t < 0)
			return (false);
	}
	rec->point = point_at(ray, rec->t);
	rec->normal = vec_scale(vec_init(sphere->center, rec->point),
			1 / sphere->radius);
	rec->color = sphere->color;
	return (true);
}

// not yet finished
bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double		denominator;
	t_vector	oc;

	oc = vec_sub(plane->point, ray->origin);
	denominator = vec_dot(ray->dir, plane->normal);
	if (denominator == 0)
	{
		rec->t = 0.0;
		return (true);
	}
	else if (denominator < 0)
	{
		plane->normal = vec_scale(plane->normal, -1.0);
		denominator = vec_dot(ray->dir, plane->normal);
	}
	rec->t = -vec_dot(oc, plane->normal) / denominator;
	rec->color = plane->color;
	return (true);
}

// not yet finished
bool	hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
{
	double		a;
	double		h;
	double		c;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cyl->center, ray->origin);
	a = vec_dot(ray->dir, ray->dir) - pow(vec_dot(ray->dir, cyl->axis), 2);
	h = vec_dot(ray->dir, oc)
		- vec_dot(ray->dir, cyl->axis) * vec_dot(oc, cyl->axis);
	c = vec_dot(oc, oc) - pow(vec_dot(oc, cyl->axis), 2) - pow(cyl->radius, 2);
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	rec->t = (h - sqrt(discriminant)) / a;
	if (rec->t < 0)
	{
		rec->t = (h + sqrt(discriminant)) / a;
		if (rec->t < 0)
			return (false);
	}
	if (rec)
	rec->color = cyl->color;
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
