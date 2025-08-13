/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/13 15:56:43 by thudinh          ###   ########.fr       */
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

//cone Definition = "((P - A) * v)^2 = cos^2 * θ ||P - A||^2" Where:
//P = a point that is on the plain so we insert or Ray point definition for P:
//P = R(t) = O +tD
//A = is the Apex point of the cone;
//v = is the axis vector pointing "down" the cones center;
//θ = is the half angle;
//after insirting our ray formula for P and much rearengment and expandsion
//we end up with this formula:
// at^2 + bt + c = 0 where:
//a = (D * v)^2 - cos^2 θ;
//b = 2((D * v)((O - A) * v)cos^2 θ((O - A) * D));
//half_b = ((D * v)((O - A) * v)cos^2 θ((O - A) * D));
//c = ((O - A) * v)^2 - cos^2 θ * ||0 - A||^2;
// if we solve now for t we will end up with:
//t= (-half_b ± √Δ) / a; where:
//Δ = half_b^2 - ac;
//if Δ is < 0 the ray never hits the cone if Δ is >= 0 it does;
bool	hit_cone(t_cone *cone, t_ray *ray, t_hit_record *rec)
{
	t_cone_var	var;
	double		t;

	t = 0.0;
	init_cone_var(&var, cone, ray);
	if (calculate_cone(&var, &t))
	{
		var.p = point_at(ray, t);
		var.u = vec_sub(var.p, cone->apex);
		var.normal = vec_sub(vec_scale(var.v, vec_dot(var.u, var.v)),
				vec_scale(var.u, var.k));
		var.normal = vec_normalize(var.normal);
		if (vec_dot(var.normal, ray->dir) > 0.0)
			var.normal = vec_scale(var.normal, -1.0);
		rec->t = t;
		update_hit_record(rec, var.p, var.normal, cone->color);
		return (true);
	}
	return (false);
}

bool	hit_triangle(t_triangle *tri, t_ray *ray, t_hit_record *rec)
{
	t_triangle_var	var;

	if (!init_triangle_var_and_check_if_parallel(&var, tri, ray))
		return (false);
	var.s = vec_sub(ray->origin, tri->v1);
	var.u = vec_dot(var.s, var.ray_cross_e2) * var.inverse_determinant;
	if ((var.u < 0.0 && fabs(var.u) > EPSILON)
		|| (var.u > 1.0 && fabs(var.u - 1) > EPSILON))
		return (false);
	var.s_cross_e1 = vec_cross(var.s, var.e1);
	var.v = vec_dot(ray->dir, var.s_cross_e1) * var.inverse_determinant;
	if ((var.v < 0.0 && fabs(var.v) > EPSILON)
		|| ((var.u + var.v) > 1.0 && fabs(var.u + var.v - 1) > EPSILON))
		return (false);
	var.t = vec_dot(var.e2, var.s_cross_e1) * var.inverse_determinant;
	if (var.t <= EPSILON)
		return (false);
	var.intersection_point = point_at(ray, var.t);
	var.normal = vec_normalize(vec_cross(var.e1, var.e2));
	if (vec_dot(var.normal, ray->dir) > 0.0)
		var.normal = vec_scale(var.normal, -1.0);
	rec->t = var.t;
	update_hit_record(rec, var.intersection_point, var.normal, tri->color);
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
