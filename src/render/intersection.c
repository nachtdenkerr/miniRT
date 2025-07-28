/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 12:19:43 by thudinh           #+#    #+#             */
/*   Updated: 2025/07/28 12:46:29 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// calculate if rays can hit the sphere
double	hit_sphere(t_sphere sphere, t_ray ray)
{
	double		a;
	double		h;
	double		c;
	double		discriminant;
	t_vector	ray_org_to_center;

	ray_org_to_center = vec_sub(sphere.center, ray.origin);
	a = vec_dot(ray.dir, ray.dir);
	h = (vec_dot(ray.dir, ray_org_to_center));
	c = vec_dot(ray_org_to_center, ray_org_to_center) - pow(sphere.radius, 2);
	discriminant = pow(h, 2) - a * c;
	if (discriminant < 0)
		return (-1.0);
	else
		return (h - sqrt(discriminant) / a);
}
