/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:34:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/28 11:55:03 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"

// Add two vectors.
t_vector	vec_add(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

// Subtract two vectors.
t_vector	vec_sub(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

// Scale vector by scalar.
t_vector	vec_scale(t_vector v, double s)
{
	t_vector	u;

	u.x *= s;
	u.y *= s;
	u.z *= s;
	return (u);
}

// Dot product.
double	vec_dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// Cross product (needed for plane / cylinder axes).
t_vector	vec_cross(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

// Get vector magnitude.
double	vec_length(t_vector v)
{
	return (sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2)));
}

// Return normalized vector.
t_vector	vec_normalize(t_vector v)
{
	t_vector	v_n;

	v_n = vec_scale(v, 1 / vec_length(v));
	return (v_n);
}

// Reflect vector v over normal n (for specular).
t_vector	vec_reflect(t_vector v, t_vector n)
{
	
}
