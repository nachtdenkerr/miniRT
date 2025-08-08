/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:34:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/08 16:02:58 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

// Get vector magnitude.
double	vec_length(t_vector v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

// Return normalized vector.
t_vector	vec_normalize(t_vector v)
{
	t_vector	v_n;
	double		length;

	length = vec_length(v);
	if (length == 0)
	{
		v_n.x = 0;
		v_n.y = 0;
		v_n.z = 0;
		return (v_n);
	}
	v_n = vec_scale(v, 1 / vec_length(v));
	return (v_n);
}

// Reflect vector v over normal n (for specular).
t_vector	vec_reflect(t_vector v, t_vector n)
{
	t_vector	w;

	w = vec_sub(v, vec_scale(n, 2.0 * vec_dot(v, n)));
	return (w);
}

t_point	point_at(t_ray *ray, double t)
{
	t_point	point;

	point.x = ray->origin.x + ray->dir.x * t;
	point.y = ray->origin.y + ray->dir.y * t;
	point.z = ray->origin.z + ray->dir.z * t;
	return (point);
}

double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}

t_vector	random_unit_vec(void)
{
	t_vector	v;

	v.x = (double)rand() / RAND_MAX * 2.0 - 1.0;
	v.y = (double)rand() / RAND_MAX * 2.0 - 1.0;
	v.z = (double)rand() / RAND_MAX * 2.0 - 1.0;
	return (vec_normalize(v));
}

t_vector	create_point(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
