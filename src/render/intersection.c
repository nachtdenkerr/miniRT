/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/11 10:57:07 by jmutschl         ###   ########.fr       */
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
	t_texture	checker;
	t_color		color;

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
	get_sphere_uv(rec, sphere->center, sphere->radius);
	checker.color1 = create_color(255, 255, 255);
	checker.color2 = create_color(0, 100, 0);
	checker.width = 30.0;
	checker.height = 20.0;
	color = checker_texture(checker, rec->u, rec->v);
	update_hit_record(rec, point_at(ray, rec->t),
		vec_normalize(vec_sub(rec->point, sphere->center)),
		color);
	return (true);
}

bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	double		denominator;
	t_vector	normal;
	t_point		point;
	t_color		color;
	t_texture	checker;

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
	checker.width = 5.0;
	checker.height = 5.0;
	checker.color1 = create_color(255, 255, 255);
	checker.color2 = create_color(0, 100, 0);
	update_hit_record(rec, point, normal, plane->color);
	get_plane_uv(rec, plane->point);
	color = checker_texture(checker, rec->u, rec->v);
	update_hit_record(rec, point, normal, color);
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
		var.normal = vec_sub(vec_scale(var.v, vec_dot(var.u, var.v)), vec_scale(var.u, var.k));
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
	(void)tri;
	(void)ray;
	(void)rec;
	return (false);
}
