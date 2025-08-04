/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/30 12:44:18 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// calculate if rays can hit the sphere
double	hit_sphere(t_sphere sphere, t_ray ray)
{
	double		a;
	double		h;
	double		c;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(sphere.center, ray.origin);
	a = vec_dot(ray.dir, ray.dir);
	h = (vec_dot(ray.dir, oc));
	c = vec_dot(oc, oc) - pow(sphere.radius, 2);
	discriminant = pow(h, 2) - a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((h - sqrt(discriminant)) / a);
}

// not yet finished
double	hit_plane(t_plane plane, t_ray ray)
{
	double		t;
	double		denominator;
	t_vector	oc;

	oc = vec_sub(plane.point, ray.origin);
	denominator = dot(ray.dir, plane.normal);
	if (denominator == 0)
		return (0.0);
	else if (denominator < 0)
	{
		plane.normal = vec_scale(plane.normal, -1.0);
		denominator = dot(ray.dir, plane.normal);
	}
	t = -vec_dot(oc, plane.normal) / denominator;
	return (t);
}

// not yet finished
double	hit_cylinder(t_cylinder cyl, t_ray ray)
{
	double		a;
	double		h;
	double		c;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cyl.center, ray.origin);
	a = vec_dot(ray.dir, ray.dir) - pow(vec_dot(ray.dir, cyl.axis), 2);
	h = vec_dot(ray.dir, oc)
		- vec_dot(ray.dir, cyl.axis) * vec_dot(oc, cyl.axis);
	c = vec_dot(oc, oc) - pow(vec_dot(oc, cyl.axis), 2) - pow(cyl.radius, 2);
	discriminant = pow(h, 2) - a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return ((h - sqrt(discriminant)) / a);
}

double	hit_cone(t_cone cone, t_ray ray)
{
	return (1);
}
