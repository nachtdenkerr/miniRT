/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 20:34:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/04 16:20:53 by thudinh          ###   ########.fr       */
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

	v_n = vec_scale(v, 1 / vec_length(v));
	return (v_n);
}

// Reflect vector v over normal n (for specular).
t_vector	vec_reflect(t_vector v, t_vector n)
{
	t_vector	w;

	w = vec_sub(v, vec_scale(n, 2.0 * vec_dot(v, n)));
}

double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180.0);
}
