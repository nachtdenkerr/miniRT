/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thudinh <thudinh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:46:15 by thudinh           #+#    #+#             */
/*   Updated: 2025/08/05 10:43:44 by thudinh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "math_utils.h"

bool	hit_sphere(t_sphere *sphere, t_ray *ray, double *t);
bool	hit_cylinder(t_cylinder *cyl, t_ray *ray, double *t);
bool	hit_plane(t_plane *plane, t_ray *ray, double *t);
bool	hit_cone(t_cone *cone, t_ray *ray, double *t);
bool	hit_sphere_wrapper(void *data, t_ray *ray, double *t);
bool	hit_cylinder_wrapper(void *data, t_ray *ray, double *t);
bool	hit_plane_wrapper(void *data, t_ray *ray, double *t);
bool	hit_cone_wrapper(void *data, t_ray *ray, double *t);

#endif