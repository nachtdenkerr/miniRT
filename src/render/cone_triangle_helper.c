/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_triangle_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 12:00:15 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/10 12:01:50 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	ft_swap(double *x, double *y)
{
	double temp;

	temp = *x;
	*x = *y;
	*y = temp;
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
