/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_board.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:05:06 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/13 15:48:54 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	checker_texture_init(t_texture *checker, double width, double height,
		double scale_val)
{
	checker->color1 = create_color(255, 255, 255);
	checker->color2 = create_color(0, 100, 0);
	checker->width = width / scale_val;
	checker->height = height / scale_val;
}

// Create a checkerboard texture based on the UV coordinates
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

// Convert a point in cartesian coordinates to UV coordinates
void	get_plane_uv(t_hit_record *rec, t_point plane_point)
{
	t_vector	normal;
	t_vector	arb_vec;
	t_vector	vec_u;
	t_vector	vec_v;
	t_vector	local_vec;

	normal = rec->normal;
	if (fabs(normal.x) < 0.9)
	{
		arb_vec.x = 1;
		arb_vec.y = 0;
		arb_vec.z = 0;
	}
	else
	{
		arb_vec.x = 0;
		arb_vec.y = 1;
		arb_vec.z = 0;
	}
	local_vec = vec_sub(rec->point, plane_point);
	vec_u = vec_normalize(vec_cross(arb_vec, normal));
	vec_v = vec_normalize(vec_cross(normal, vec_u));
	rec->u = vec_dot(local_vec, vec_u) / 5.0;
	rec->v = vec_dot(local_vec, vec_v) / 5.0;
}

// Convert a point in cartesian coordinates to UV coordinates for a sphere
void	get_sphere_uv(t_hit_record *rec, t_point sp_center, double radius)
{
	double		theta;
	double		phi;
	double		clamped_y;
	t_vector	local_vec;

	local_vec = vec_sub(rec->point, sp_center);
	clamped_y = fmin(fmax(local_vec.y / radius, -1.0), 1.0);
	phi = acos(clamped_y);
	theta = atan2(local_vec.z, local_vec.x);
	rec->u = (theta + M_PI) / (2 * M_PI);
	rec->v = 1 - phi / M_PI;
}
