/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 09:37:40 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/07 10:50:40 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	update_hit_record(t_hit_record *rec, t_point point, t_vector normal,
	t_color color)
{
	rec->point = point;
	rec->normal = normal;
	rec->color = color;
}

double	*solve_t_values(t_cylinder *cyl, t_ray *ray)
{
	double		a;
	double		h;
	double		discriminant;
	t_vector	oc;
	double		*result;

	oc = vec_sub(ray->origin, cyl->center);
	a = vec_dot(ray->dir, ray->dir) - pow(vec_dot(ray->dir, cyl->axis), 2);
	h = vec_dot(ray->dir, oc)
		- vec_dot(ray->dir, cyl->axis) * vec_dot(oc, cyl->axis);
	discriminant = h * h - a * (vec_dot(oc, oc) - pow(vec_dot(oc, cyl->axis), 2)
			- pow(cyl->radius, 2));
	if (discriminant < 0.0)
		return (NULL);
	result = malloc(2 * sizeof(double));
	if (!result)
		return (NULL);
	result[0] = (-h - sqrt(discriminant)) / a;
	result[1] = (-h + sqrt(discriminant)) / a;
	return (result);
}

bool	check_t_value(t_cylinder *cyl, t_ray *ray,
	t_hit_record *rec, double t_value)
{
	double		axis_projection;
	t_point		point;
	t_vector	vec_cyl_center_point;
	t_vector	vec_scaled_cyl_axis;

	point = point_at(ray, t_value);
	vec_cyl_center_point = vec_sub(point, cyl->center);
	axis_projection = vec_dot(vec_cyl_center_point, cyl->axis);
	if (fabs(axis_projection) > cyl->height / 2)
		return (false);
	rec->t = t_value;
	vec_scaled_cyl_axis = vec_scale(cyl->axis, axis_projection);
	update_hit_record(rec, point,
		vec_normalize(vec_sub(vec_cyl_center_point, vec_scaled_cyl_axis)),
		cyl->color);
	return (true);
}
