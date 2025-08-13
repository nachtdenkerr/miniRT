/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:52:46 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/13 18:00:14 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	hit_cyl_body(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
{
	double		*t_values;
	int			i;
	t_vector	axis;

	axis = cyl->axis;
	t_values = solve_t_values(cyl, ray, axis);
	if (!t_values)
		return (false);
	i = -1;
	while (++i < 2)
	{
		if (t_values[i] < EPSILON)
			continue ;
		if (check_t_value(cyl, ray, rec, t_values[i]) == false)
			continue ;
		free(t_values);
		return (true);
	}
	free(t_values);
	return (false);
}

bool	hit_cylinder_topcap(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
{
	double		t;
	t_vector	axis;
	t_point		cap_center;
	double		denominator;
	double		point_center_proj;

	axis = cyl->axis;
	cap_center = vec_add(cyl->center, vec_scale(axis, cyl->height / 2));
	denominator = vec_dot(ray->dir, axis);
	if (fabs(denominator) < EPSILON)
		return (false);
	t = vec_dot(vec_sub(cap_center, ray->origin), axis) / denominator;
	if (t < 0)
		return (false);
	point_center_proj = vec_dot(vec_sub(point_at(ray, t), cap_center),
			vec_sub(point_at(ray, t), cap_center));
	if (point_center_proj > cyl->radius * cyl->radius)
		return (false);
	rec->t = t;
	if (vec_dot(axis, ray->dir) > 0.0)
		axis = vec_scale(axis, -1.0);
	update_hit_record(rec, point_at(ray, t), axis, cyl->color);
	return (true);
}

bool	hit_cylinder_botcap(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
{
	double		t;
	t_vector	axis;
	t_point		cap_center;
	double		denominator;
	double		point_center_proj;

	axis = cyl->axis;
	axis = vec_scale(axis, -1.0);
	cap_center = vec_add(cyl->center, vec_scale(axis, cyl->height / 2));
	denominator = vec_dot(ray->dir, axis);
	if (fabs(denominator) < EPSILON)
		return (false);
	t = vec_dot(vec_sub(cap_center, ray->origin), axis) / denominator;
	if (t < 0)
		return (false);
	point_center_proj = vec_dot(vec_sub(point_at(ray, t), cap_center),
			vec_sub(point_at(ray, t), cap_center));
	if (point_center_proj > cyl->radius * cyl->radius)
		return (false);
	rec->t = t;
	if (vec_dot(axis, ray->dir) > 0.0)
		axis = vec_scale(axis, -1.0);
	update_hit_record(rec, point_at(ray, t), axis, cyl->color);
	return (true);
}

// This function checks if a ray intersects with a cylinder 
// (body, top cap, or bottom cap).
// Solve the quadratic equation to find the intersection points.
// Solve the finite plane intersection for the top and bottom caps.
bool	hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
{
	t_hit_record	tmp_rec;
	bool			hit;
	double			closest_t;

	hit = false;
	closest_t = INFINITY;
	if (hit_cyl_body(cyl, ray, &tmp_rec) && tmp_rec.t < closest_t)
	{
		*rec = tmp_rec;
		closest_t = tmp_rec.t;
		hit = true;
	}
	if (hit_cylinder_topcap(cyl, ray, &tmp_rec) && tmp_rec.t < closest_t)
	{
		*rec = tmp_rec;
		closest_t = tmp_rec.t;
		hit = true;
	}
	if (hit_cylinder_botcap(cyl, ray, &tmp_rec) && tmp_rec.t < closest_t)
	{
		*rec = tmp_rec;
		closest_t = tmp_rec.t;
		hit = true;
	}
	return (hit);
}
