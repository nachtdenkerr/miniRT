/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:05:06 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/08 14:26:31 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

t_color	checker_texture(t_texture checker, double u, double v)
{
	double	u2;
	double	v2;

	u2 = fabs(floor(u * checker.width));
	v2 = fabs(floor(v * checker.height));
	if (((int)u2 + (int)v2) % 2 == 0)
		return (checker.color1);
	else
		return (checker.color2);
}

void	get_plane_uv(t_hit_record *rec, t_point plane_point)
{
	t_vector	normal;
	t_vector	arb_vec;
	t_vector	vec_u;
	t_vector	vec_v;
	t_vector	local_vec;

	normal = rec->normal;
	if (fabs(normal.x) < 0.9)
		arb_vec = create_point(1, 0, 0);
	else
		arb_vec = create_point(0, 1, 0);
	local_vec = vec_sub(rec->point, plane_point);
	vec_u = vec_normalize(vec_cross(arb_vec, normal));
	vec_v = vec_normalize(vec_cross(normal, vec_u));
	rec->u = vec_dot(local_vec, vec_u) / 5.0;
	rec->v = vec_dot(local_vec, vec_v) / 5.0;
	rec->u = fmod(rec->u, 1.0);
	rec->v = fmod(rec->v, 1.0);
}

void	get_sphere_uv(t_hit_record *rec, t_point sp_center, double radius)
{
	double		theta;
	double		phi;
	double		raw_u;
	double		clamped_y;
	t_vector	local_vec;

	local_vec = vec_sub(rec->point, sp_center);
	clamped_y = fmin(fmax(local_vec.y / radius, -1.0), 1.0);
	phi = acos(local_vec.y);
	theta = atan2(local_vec.z, local_vec.x);
	raw_u = theta / (2 * M_PI);
	rec->u = 1 - (raw_u + 0.5);
	rec->v = 1 - phi / M_PI;
}
