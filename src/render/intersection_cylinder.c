/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 11:52:46 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/06 16:38:28 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double	*solve_t_values(t_cylinder *cyl, t_ray *ray)
{
	double		a;
	double		h;
	double		c;
	double		discriminant;
	t_vector	oc;
	double		*result;

	oc = vec_sub(ray->origin, cyl->center);
	a = vec_dot(ray->dir, ray->dir) - pow(vec_dot(ray->dir, cyl->axis), 2);
	h = vec_dot(ray->dir, oc)
		- vec_dot(ray->dir, cyl->axis) * vec_dot(oc, cyl->axis);
	c = vec_dot(oc, oc) - pow(vec_dot(oc, cyl->axis), 2)
		- pow(cyl->radius, 2);
	discriminant = h * h - a * c;
	if (discriminant < 0.0)
		return (NULL);
	result = malloc(2 * sizeof(double));
	if (!result)
		return (NULL);
	result[0] = (-h - sqrt(discriminant)) / a;
	result[1] = (-h + sqrt(discriminant)) / a;
	return (result);
}

bool	hit_cyl_body(t_cylinder *cyl, t_ray *ray, t_hit_record *rec, double *closest_t)
{
	double		*t_values;
	int			i;
	t_point		point;
	double		axis_projection;

	t_values = solve_t_values(cyl, ray);
	if (!t_values)
		return (false);
	i = 0;
	while (i < 2)
	{
		if (t_values[i] < EPSILON || t_values[i] > *closest_t)
		{
			i++;
			continue ;
		}
		if (t_values[i] < *closest_t)
		{
			point = point_at(ray, t_values[i]);
			axis_projection = vec_dot(vec_sub(point, cyl->center), cyl->axis);
			if (fabs(axis_projection) > cyl->height / 2)
			{
				i++;
				continue ;
			}
			rec->t = t_values[i];
			rec->point = point;
			rec->normal = vec_normalize(vec_sub(vec_sub(point, cyl->center),
						vec_scale(cyl->axis, axis_projection)));
			rec->color = cyl->color;
			*closest_t = rec->t;
			return (free(t_values), true);
		}
		i++;
	}
	return (free(t_values), false);
}

bool	hit_cylinder_topcap(t_cylinder *cyl, t_ray *ray, t_hit_record *rec,
			double *closest_t)
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
	if (t < 0 || t > *closest_t)
		return (false);
	rec->point = point_at(ray, t);
	point_center_proj = vec_dot(vec_sub(rec->point, cap_center),
			vec_sub(rec->point, cap_center));
	if (point_center_proj > cyl->radius * cyl->radius)
		return (false);
	rec->normal = axis;
	rec->color = cyl->color;
	rec->t = t;
	return (true);
}

bool	hit_cylinder_botcap(t_cylinder *cyl, t_ray *ray, t_hit_record *rec,
			double *closest_t)
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
	if (t < 0 || t > *closest_t)
		return (false);
	rec->point = point_at(ray, t);
	point_center_proj = vec_dot(vec_sub(rec->point, cap_center),
			vec_sub(rec->point, cap_center));
	if (point_center_proj > cyl->radius * cyl->radius)
		return (false);
	rec->normal = axis;
	rec->color = cyl->color;
	rec->t = t;
	return (true);
}

bool	hit_cylinder(t_cylinder *cyl, t_ray *ray, t_hit_record *rec)
{
	t_hit_record	tmp_rec;
	double			closest_t;
	bool			hit;

	closest_t = INFINITY;
	hit = false;
	if (hit_cyl_body(cyl, ray, &tmp_rec, &closest_t))
	{
		printf("hit_cyl_body hit at t: %f\n", tmp_rec.t);
		*rec = tmp_rec;
		hit = true;
	}
	if (hit_cylinder_topcap(cyl, ray, &tmp_rec, &closest_t))
	{
		printf("hit_cylinder_topcap hit at t: %f\n", tmp_rec.t);
		*rec = tmp_rec;
		hit = true;
	}
	if (hit_cylinder_botcap(cyl, ray, &tmp_rec, &closest_t))
	{
		printf("hit_cylinder_botcap hit at t: %f\n", tmp_rec.t);
		*rec = tmp_rec;
		hit = true;
	}
	return (hit);
}
