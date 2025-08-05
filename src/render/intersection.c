/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/04 16:41:28 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// calculate if rays can hit the sphere
bool	hit_sphere(t_sphere sphere, t_ray ray, double *t)
{
	double		a;
	double		h;
	double		c;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(sphere.center, ray.origin);
	a = vec_dot(ray.dir, ray.dir);
	h = (vec_dot(ray.dir, oc));
	c = vec_dot(oc, oc) - sphere.radius * sphere.radius;
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	*t = (h - sqrt(discriminant)) / a;
	if (*t < 0)
	{
		*t = (h + sqrt(discriminant)) / a;
		if (*t < 0)
			return (false);
	}
	return (true);
}

// not yet finished
bool	hit_plane(t_plane plane, t_ray ray, double *t)
{
	double		t;
	double		denominator;
	t_vector	oc;

	oc = vec_sub(plane.point, ray.origin);
	denominator = dot(ray.dir, plane.normal);
	if (denominator == 0)
	{
		*t = 0.0;
		return (true);
	}
	else if (denominator < 0)
	{
		plane.normal = vec_scale(plane.normal, -1.0);
		denominator = dot(ray.dir, plane.normal);
	}
	*t = -vec_dot(oc, plane.normal) / denominator;
	return (true);
}

// not yet finished
bool	hit_cylinder(t_cylinder cyl, t_ray ray, double *t)
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
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	*t = (h - sqrt(discriminant)) / a;
	if (*t < 0)
	{
		*t = (h + sqrt(discriminant)) / a;
		if (*t < 0)
			return (false);
	}
	ray.hit_point = vec_scale(ray.dir, *t);
	ray.hit_point = vec_add(ray.origin, ray.hit_point);
	if (ray.hit_point.x < cyl.center.x - cyl.radius
		|| ray.hit_point.x > cyl.center.x + cyl.radius
		|| ray.hit_point.y < cyl.center.y - cyl.radius
		|| ray.hit_point.y > cyl.center.y + cyl.radius
		|| ray.hit_point.z < cyl.center.z
		|| ray.hit_point.z > cyl.center.z + cyl.height)
		return (false);
	return (true);
}

bool	hit_cone(t_cone cone, t_ray ray, double *t)
{
	double		a;
	double		h;
	double		c;
	double		k_sqr;
	double		discriminant;
	t_vector	oc;

	oc = vec_sub(cone.apex, ray.origin);
	k_sqr = tan(deg_to_rad(cone.angle)) * tan(deg_to_rad(cone.angle));
	a = vec_dot(ray.dir, ray.dir)
		- (1 + k_sqr) * pow(vec_dot(ray.dir, cone.axis), 2);
	h = vec_dot(ray.dir, oc) - (1 + k_sqr) * vec_dot(ray.dir, cone.axis)
		* vec_dot(oc, cone.axis);
	c = vec_dot(oc, oc) - (1 + k_sqr) * pow(vec_dot(oc, cone.axis), 2);
	discriminant = h * h - a * c;
	if (discriminant < 0)
		return (false);
	*t = (h - sqrt(discriminant)) / a;
	return (true);
}

bool	hit_object(t_ray *ray, t_scene *scene, double *t)
{
	double		t_tmp;
	bool		hit;

	hit = false;
	object = scene->objects;
	while (object)
	{
		if (object->type == SPHERE)
			hit = hit_sphere(object->sphere, *ray, &t_tmp);
		else if (object->type == PLANE)
			hit = hit_plane(object->plane, *ray, &t_tmp);
		else if (object->type == CYLINDER)
			hit = hit_cylinder(object->cylinder, *ray, &t_tmp);
		else if (object->type == CONE)
			hit = hit_cone(object->cone, *ray, &t_tmp);
		if (hit && t_tmp < *t)
		{
			*t = t_tmp;
			ray->hit_point = vec_add(ray->origin, vec_scale(ray->dir, *t));
			return (true);
		}
		object = object->next;
	}
	return (false);
}
