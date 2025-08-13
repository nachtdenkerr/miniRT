/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_triangle_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:00:15 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/13 15:54:00 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	ft_swap(double *x, double *y)
{
	double	temp;

	temp = *x;
	*x = *y;
	*y = temp;
}

//for our triangle we use the Möller–Trumbore intersection algorithm
//
//which is defiend like that:
// 		O + tD = v0 + u * e1 + v * e2
//	where:
//		O = ray origin;
//		D = ray direction;
//		v1, v2, v3 = trianlge corner points;
//		e1 = v2 - v1; basically dir_vec of one ofthe edges of the triangle;
//		e2 = v3 - v1; basically dir_vec of one ofthe edges of the triangle;
//		u,v = barycentric coordinates (0 <= u <= 1, 0 <= v <= 1, u+v <= 1);
//		t = distance along the ray to the intersection (what we wanna solve for)
bool	init_triangle_var_and_check_if_parallel(t_triangle_var *var,
	t_triangle *tri, t_ray *ray)
{
	var->e1 = vec_sub(tri->v2, tri->v1);
	var->e2 = vec_sub(tri->v3, tri->v1);
	var->ray_cross_e2 = vec_cross(ray->dir, var->e2);
	var->determinant = vec_dot(var->e1, var->ray_cross_e2);
	if (fabs(var->determinant) < EPSILON)
		return (false);
	var->inverse_determinant = 1.0 / var->determinant;
	return (true);
}

void	init_cone_var(t_cone_var *var, t_cone *cone, t_ray *ray)
{
	var->v = cone->axis;
	var->w = vec_sub(ray->origin, cone->apex);
	var->m = vec_dot(ray->dir, var->v);
	var->n = vec_dot(var->w, var->v);
	var->k = cos(cone->angle) * cos(cone->angle);
	var->a = (var->m * var->m) - var->k;
	var->half_b = var->m * var->n - var->k * vec_dot(var->w, ray->dir);
	var->c = var->n * var->n - var->k * vec_dot(var->w, var->w);
	var->delta = var->half_b * var->half_b - var->a * var->c;
}

bool	calculate_cone(t_cone_var *var, double *t)
{
	if (fabs(var->a) < EPSILON)
	{
		if (fabs(var->half_b) < EPSILON)
			return (false);
		*t = -var->c / (2.0 * var->half_b);
		if (*t <= EPSILON)
			return (false);
	}
	else
	{
		if (var->delta < 0.0)
			return (false);
		var->s = sqrt(var->delta);
		var->tx_minus = (-(var->half_b) - var->s) / var->a;
		var->tx_plus = (-(var->half_b) + var->s) / var->a;
		if (var->tx_minus > var->tx_plus)
			ft_swap(&var->tx_minus, &var->tx_plus);
		if (var->tx_minus > EPSILON)
			*t = var->tx_minus;
		else if (var->tx_plus > EPSILON)
			*t = var->tx_plus;
		else
			return (false);
	}
	return (true);
}
