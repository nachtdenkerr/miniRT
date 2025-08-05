/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:22:25 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/05 15:03:11 by thudinh          ###   ########.fr       */
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

	u.x = v.x * s;
	u.y = v.y * s;
	u.z = v.z * s;
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
