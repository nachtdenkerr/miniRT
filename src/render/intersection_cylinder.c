/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:52:46 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/07 11:19:45 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

bool	hit_cyl_body(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
{
	double		*t_values;
	int			i;

	t_values = solve_t_values(cyl, ray);
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
	point_center_proj = vec_dot(vec_sub(rec->point, cap_center),
			vec_sub(rec->point, cap_center));
	if (point_center_proj > cyl->radius * cyl->radius)
		return (false);
	rec->t = t;
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
	cap_center = vec_sub(cyl->center, vec_scale(axis, cyl->height / 2));
	denominator = vec_dot(ray->dir, axis);
	if (fabs(denominator) < EPSILON)
		return (false);
	t = vec_dot(vec_sub(cap_center, ray->origin), axis) / denominator;
	if (t < 0)
		return (false);
	point_center_proj = vec_dot(vec_sub(rec->point, cap_center),
			vec_sub(rec->point, cap_center));
	if (point_center_proj > cyl->radius * cyl->radius)
		return (false);
	rec->t = t;
	update_hit_record(rec, point_at(ray, t), vec_scale(axis, -1.0),
		cyl->color);
	return (true);
}

bool	hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
{
	t_hit_record	tmp_rec;
	bool			hit;

	hit = false;
	if (hit_cyl_body(cyl, ray, &tmp_rec))
	{
		*rec = tmp_rec;
		hit = true;
	}
	if (hit_cylinder_topcap(cyl, ray, &tmp_rec))
	{
		*rec = tmp_rec;
		hit = true;
	}
	if (hit_cylinder_botcap(cyl, ray, &tmp_rec))
	{
		*rec = tmp_rec;
		hit = true;
	}
	return (hit);
}
