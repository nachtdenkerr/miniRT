/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmutschl <jmutschl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:42:09 by jmutschl          #+#    #+#             */
/*   Updated: 2025/08/14 10:07:48 by jmutschl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

// Get an arbitrary vector that is not parallel to the camera's forward vector
t_vector	get_up_tmp(t_vector forward)
{
	t_vector	up_tmp;

	if (fabs(forward.y) > 0.99)
	{
		up_tmp.x = 0;
		up_tmp.y = 0;
		up_tmp.z = 1;
	}
	else
	{
		up_tmp.x = 0;
		up_tmp.y = 1;
		up_tmp.z = 0;
	}
	return (up_tmp);
}

// Calculate the 2 orthogonal vectors (right and up) 
//based on the camera's orientation
t_vector	compute_ray_direction_helper(double x_ndc, double y_ndc,
		double aspect_ratio, t_scene *scene)
{
	double		angle;
	t_vector	cam_right;
	t_vector	cam_up;
	t_vector	cam_forward;
	t_vector	up_tmp;

	cam_forward = scene->camera.orientation;
	angle = tan(scene->camera.fov * 0.5 * M_PI / 180.0);
	up_tmp = get_up_tmp(cam_forward);
	cam_right = vec_normalize(vec_cross(up_tmp, cam_forward));
	cam_up = vec_normalize(vec_cross(cam_forward, cam_right));
	return (vec_normalize(vec_add(vec_add(vec_scale(cam_right, x_ndc
						* aspect_ratio * angle), vec_scale(cam_up, y_ndc
						* angle)), cam_forward)));
}

t_vector	compute_ray_direction(int i, int j, t_scene *scene)
{
	double		x_ndc;
	double		y_ndc;
	double		aspect_ratio;
	t_vector	result;

	x_ndc = 2.0 * ((i + 0.5) / (double)WIDTH) - 1.0;
	y_ndc = 1.0 - 2.0 * ((j + 0.5) / (double)HEIGHT);
	aspect_ratio = (double)WIDTH / (double)HEIGHT;
	result = compute_ray_direction_helper(x_ndc, y_ndc, aspect_ratio, scene);
	return (result);
}

// Calculate the ray direction and origin for each pixel
// in the scene based on the camera's position and orientation.
void	init_ray(t_ray *ray, t_scene *scene, int i, int j)
{
	ray->dir = compute_ray_direction(i, j, scene);
	ray->origin = scene->camera.position;
}
